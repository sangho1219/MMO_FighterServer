#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Winmm")
#include <WinSock2.h> 
#include "session.h"

#define SERVERPORT 20000

SOCKET listensock;

int networkInit();
void netIOProcess();
void netSelectSocket(SOCKET* SockArr, FD_SET* rset, FD_SET* wset);
bool netProc_Send(SOCKET sock);
bool netProc_Recv(SOCKET sock);
void netProc_Accept();





//소켓 통신을 위한 초기화
int networkInit()
{
	//WSAStartup()
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	//socket() - listensock
	listensock = socket(AF_INET, SOCK_STREAM, 0);
	if (listensock == INVALID_SOCKET)
	{
		printf("-socket() - listen ERROR : %d\n", WSAGetLastError());
		return 0;
	}

	//bind() - listensock
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(SERVERPORT);
	addr.sin_family = AF_INET;

	int bindVal = bind(listensock, (SOCKADDR*)&addr, sizeof(addr));
	if (bindVal == SOCKET_ERROR)
	{
		printf("-bind() - listensock ERROR : %d\n", WSAGetLastError());
		return 0;
	}

	//ioctlsocket() - listensock
	u_long nonBlock = 1;
	int ioctlVal = ioctlsocket(listensock, FIONBIO, &nonBlock);
	if (ioctlVal == SOCKET_ERROR)
	{
		printf("-ioctlsocket() - listensock ERROR : %d\n", WSAGetLastError());
		return 0;
	}

	//listen() - listensock 
	int listenVal = listen(listensock, SOMAXCONN);
	if (listenVal == SOCKET_ERROR)
	{
		printf("listen() - listensock : %d\n", WSAGetLastError());
		return 0;
	}

	//setsockopt - Linger
	LINGER Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;
	setsockopt(listensock, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(LINGER));
}

//소켓을 64개씩 끊어서 select함수를 호출시키는 함수
void netIOProcess()
{
	SESSION* pSession;

	SOCKET SockArr[FD_SETSIZE];
	FD_SET wset, rset;


	FD_ZERO(&wset);
	FD_ZERO(&rset);
	int count = 0;


	FD_SET(listensock, &rset);
	SockArr[count++] = listensock;

	//FD_SET INIT
	std::map<SOCKET, SESSION*>::iterator iter;
	for (iter = SessionMap.begin(); iter != SessionMap.end(); iter++)
	{
		pSession = iter->second;
		SockArr[count++] = pSession->Socket;

		FD_SET(pSession->Socket, &rset);
		if (pSession->SendQ.GetUseSize())
			FD_SET(pSession->Socket, &wset);

		//netSelectSocket 내부에서 세션 삭제 발생시 이터레이터 문제 방지

		if (count >= FD_SETSIZE)
		{
			netSelectSocket(SockArr, &rset, &wset);
			FD_ZERO(&rset);
			FD_ZERO(&wset);
			memset(SockArr, INVALID_SOCKET, sizeof(SOCKET) * FD_SETSIZE);
			count = 0;
			FD_SET(listensock, &rset);
			SockArr[count++] = listensock;
		}
	}
	if (count > 0) 
		netSelectSocket(SockArr, &rset, &wset);
}


//netIOProcessd에서 넘겨 받은 64개 소켓을 select하여 send와 recv를 하는 함수
//listen 소켓에 반응이 오면 accpetproc를 호출
void netSelectSocket(SOCKET* SockArr, FD_SET* rset, FD_SET* wset)
{
	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 0;

	bool procFlag = true; //send실패시 recv하지 않기 위한 플래그

	int result = select(0, rset, wset, 0, &time);

	if (result == 0)
		return;
	else if (result < 0)	//에러 로깅
		return;

	for (int i = 0; i < FD_SETSIZE && result > 0; i++)
	{
		procFlag = true;

		if (SockArr[i] == INVALID_SOCKET) continue;


		if (FD_ISSET(SockArr[i], wset))
		{
			--result;
			procFlag = netProc_Send(SockArr[i]);
		}
		if (FD_ISSET(SockArr[i], rset))
		{
			--result;
			if (procFlag)
			{
				if (SockArr[i] == listensock)
					netProc_Accept();
				else
					netProc_Recv(SockArr[i]);
			}
		}
	}
}


//세션 send큐에 있는 것 send
bool netProc_Send(SOCKET sock)
{
	SESSION* pSession = FindSession(sock);
	if (pSession == nullptr)
		return false;
	int size = pSession->SendQ.GetUseSize();

	int sendVal;


	if (size > pSession->SendQ.DirectDequeueSize())
	{
		char* tempbuf = (char*)malloc(size);
		if (tempbuf == nullptr)
			return false;
		pSession->SendQ.Dequeue(tempbuf, size);
		sendVal = send(sock, tempbuf, size, 0);
		free(tempbuf);
	}
	else
	{
		sendVal = send(sock, pSession->SendQ.GetFrontBufferPtr(), size, 0);
		if (sendVal == SOCKET_ERROR)
		{
			printf("%d\n", WSAGetLastError());
		}
		char* pp = pSession->SendQ.GetFrontBufferPtr();
		pp = pp + 3;
		if (*((int*)pp) == 0xffffffff)
			printf("Df");
		pSession->SendQ.MoveFront(size);
	}

	if (sendVal < size)
	{
		pSession->Valid = false;
		printf("send fail\n");
		//로깅, 연결을 끊어버려야 하는 케이스

		return false;	
	}

	return true;
}


//세션 recv큐에 recv
bool netProc_Recv(SOCKET sock)
{
	SESSION* pSession = FindSession(sock);
	if (pSession == nullptr)
		return false;
	RingQueue* Queue = &(pSession->RecvQ);

	int recvVal;

	recvVal = recv(sock, Queue->GetRearBufferPtr(), Queue->DirectEnqueueSize(), 0);
	if (recvVal == SOCKET_ERROR || recvVal == 0)
	{
		//로깅, 연결을 끊어버려야 하는 케이스
		pSession->Valid = false;
		if (recvVal == SOCKET_ERROR)
			printf("recv 실패 : %d\n", WSAGetLastError());
		else
			printf("연결 종료\n");
		
		return false;
	}
	Queue->MoveRear(recvVal);
	RecvQueue.push(pSession);
	pSession->LastRecvTime = timeGetTime();
	return true;
}


//listen소켓에 반응이 오면 해당 함수 호출
//accept큐에 accpet한 소켓을 넣고 함수 종료
void netProc_Accept()
{
	SOCKADDR_IN clientaddr;
	int clientaddrlen = sizeof(clientaddr);
	SOCKET client = accept(listensock, (SOCKADDR*)&clientaddr, &clientaddrlen);
	if (client == INVALID_SOCKET)
	{
		return;
	}
	SESSION* pSession = CreateSession(client);
	pSession->LastRecvTime = timeGetTime();
	AcceptQueue.push(pSession);
}


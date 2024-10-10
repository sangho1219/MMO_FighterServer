#pragma once
#include <map>
#include <queue> 
#include "Protocol.h"
#include "CircularBuffer.h"
#include "SerializationBuffer.h"
struct SESSION
{
	int check;
	bool Valid;
	SOCKET Socket;
	DWORD SessionID;


	RingQueue RecvQ;
	RingQueue SendQ;

	DWORD LastRecvTime;

	SESSION() : RecvQ(2000), SendQ(2000)
	{
		Socket = 0; SessionID = 0; LastRecvTime = 0; Valid = true; check = 9999;
	}
};


std::queue<SESSION*> AcceptQueue;
std::queue<SESSION*> RecvQueue;
std::map <SOCKET, SESSION*> SessionMap;



SESSION* CreateSession(SOCKET Socket);
SESSION* FindSession(SOCKET Socket);
bool DisconnectSession(SOCKET Socket);
















SESSION* CreateSession(SOCKET Socket)
{
	static DWORD ID = 1;


	SESSION* ses = new SESSION;
	ses->SessionID = ID++;
	ses->Socket = Socket;
	SessionMap.insert(std::pair<SOCKET, SESSION*>(Socket, ses));

	return ses;
}
SESSION* FindSession(SOCKET Socket)
{
	std::map <SOCKET, SESSION*>::iterator iter;

	iter = SessionMap.find(Socket);

	if (iter == SessionMap.end())
		return nullptr;
	else
		return iter->second;
}
bool DisconnectSession(SOCKET Socket)
{
	SESSION* ses = FindSession(Socket);
	if (ses == nullptr)
	{
		//·Î±ë
		return false;
	}
	SessionMap.erase(Socket);
	closesocket(Socket);
	free(ses);
	return true;
}



void SendSession(SESSION* pSession)
{
	if(pSession->SendQ.GetFreeSize() < serialbuf.useSize())
	{
		//·Î±ë
		pSession->Valid = false;
	}
	pSession->SendQ.Enqueue(serialbuf.getBufferPtr(), serialbuf.useSize());
}


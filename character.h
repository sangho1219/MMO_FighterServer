#pragma once
#include "network.h"
#include "session.h"
#include <list>

#define RANGE_MOVE_TOP		0
#define RANGE_MOVE_LEFT		0
#define RANGE_MOVE_RIGHT	6400
#define RANGE_MOVE_BOTTOM	6400

#define SECTOR_X			100
#define SECTOR_Y			100

#define ERROR_RANGE			50
#define ATTACK1_RANGE_X		80
#define ATTACK2_RANGE_X		90
#define ATTACK3_RANGE_X		100
#define ATTACK1_RANGE_Y		10
#define ATTACK2_RANGE_Y		10
#define ATTACK3_RANGE_Y		20

struct SECTOR_POS
{
	int x;
	int y;
};
struct SECTOR_AROUND
{
	int count;
	SECTOR_POS Around[9];
};
struct CHARACTER
{
	bool valid;
	int check;

	SESSION* session;
	DWORD characterID;
	
	unsigned char Direction;
	unsigned char Action;
	unsigned short X; unsigned short Y;

	char HP;

	SECTOR_POS cur;
	SECTOR_POS old;
};




std::map <DWORD, CHARACTER*> CharacterMap;
std::map <DWORD, CHARACTER*> SesID_CharMap;
std::list<CHARACTER*> Sector[(RANGE_MOVE_BOTTOM / SECTOR_Y) + 1][(RANGE_MOVE_RIGHT / SECTOR_X) + 1];




void SectorSendBuf(int x, int y, const CHARACTER* except);
void Unicast(const CHARACTER* ch);
void CharacterAroundCast(const CHARACTER* ch, bool check);
void SpecificSectorsCast(const SECTOR_AROUND* castSector);




void SetCurSector(unsigned short x, unsigned short y, SECTOR_POS* arg);
void GetAround(const SECTOR_POS* pos, SECTOR_AROUND* around);


CHARACTER* FindCharacter(DWORD ID);
CHARACTER* CreateCharacter();
bool DisconnectCharacter(DWORD ID);
CHARACTER* FindID(DWORD sID);
void CreateID(DWORD sID, CHARACTER*);
bool DisconnectID(DWORD sID);



void AcceptProc();


void DequeProc();
void MessageDeque(CHARACTER* ch);
void MessageCall(int messageType, CHARACTER* ch);
void MoveCall(CHARACTER* ch);
void StopCall(CHARACTER* ch);
void Attack1Call(CHARACTER* ch);
void Attack2Call(CHARACTER* ch);
void Attack3Call(CHARACTER* ch);
void EchoCall(CHARACTER* ch);
void MoveProc_Content(unsigned char Action, unsigned short X, unsigned short Y, CHARACTER* ch);
void StopProc_Content(unsigned char Direction, unsigned short X, unsigned short Y, CHARACTER* ch);
void Attack1Proc_Content(unsigned char Direction, unsigned short X, unsigned short Y, CHARACTER* ch);
void EchoProc_Content(unsigned int Time, CHARACTER* ch);


void DeleteProc();



void Update();
void SectorChange(CHARACTER* ch);
void MoveLogic(CHARACTER* ch);







void mpMyCreate(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y, unsigned char HP);
void mpDelete(unsigned int ID);
void mpOtherCreate(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y, unsigned char HP);
void mpMoveStar(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y);
void mpMoveStop(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y);
void mpAttack1(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y);
void mpAttack2(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y);
void mpAttack3(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y);
void mpDamage(unsigned int AttackID, unsigned int DamageID, unsigned char DamageHP);
void mpSYNC(unsigned int ID, unsigned short X, unsigned short Y);



//
void mpMyCreate(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y, unsigned char HP)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_CREATE_MY_CHARACTER;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	serialbuf << HP;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpOtherCreate(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y, unsigned char HP)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_CREATE_OTHER_CHARACTER;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	serialbuf << HP;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpMoveStar(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_MOVE_START;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpSYNC(unsigned int ID, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_SYNC;
	serialbuf << ID;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpDelete(unsigned int ID)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_DELETE_CHARACTER;
	serialbuf << ID;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpMoveStop(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_MOVE_STOP;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpAttack1(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_ATTACK1;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpAttack2(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_ATTACK2;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpAttack3(unsigned int ID, unsigned char Direction, unsigned short X, unsigned short Y)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_ATTACK3;
	serialbuf << ID;
	serialbuf << Direction;
	serialbuf << X;
	serialbuf << Y;
	char* p = serialbuf.getBufferPtr() + sizeof(BYTE);
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpDamage(unsigned int AttackID, unsigned int DamageID, unsigned char DamageHP)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_DAMAGE;
	serialbuf << AttackID;
	serialbuf << DamageID;
	serialbuf << DamageHP;
	char* p = serialbuf.getBufferPtr() + 1;
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}
void mpEcho(unsigned int Time)
{
	serialbuf << (BYTE)0x89;
	serialbuf.moveRear(sizeof(BYTE));
	serialbuf << (BYTE)dfPACKET_SC_ECHO;
	serialbuf << Time;
	char* p = serialbuf.getBufferPtr() + 1;
	*p = (BYTE)(serialbuf.useSize() - sizeof(mHEADER));
}









//
void SectorSendBuf(int x, int y, const CHARACTER* except)
{
	std::list<CHARACTER*>::iterator iter;
	std::list<CHARACTER*>* lst = &(Sector[y][x]);
	for (iter = lst->begin(); iter != lst->end(); iter++)
	{
		if ((*iter) == except)
		{
			continue;
		}
		SendSession((*iter)->session);
	}
}
void CharacterAroundCast(const CHARACTER* ch, bool sendMe = false)
{
	SECTOR_AROUND castSector;
	GetAround(&ch->cur, &castSector);

	int x, y;

	for (int i = 1; i < castSector.count; i++)
	{
		x = castSector.Around[i].x;
		y = castSector.Around[i].y;

		SectorSendBuf(x, y, nullptr);
	}

	x = castSector.Around[0].x;
	y = castSector.Around[0].y;

	if (sendMe)
		SectorSendBuf(x, y, nullptr);
	else
		SectorSendBuf(x, y, ch);

	serialbuf.clear();
}
void SpecificSectorsCast(const SECTOR_AROUND* castSector)
{
	for (int i = 0; i < castSector->count; i++)
	{
		int x = castSector->Around[i].x;
		int y = castSector->Around[i].y;

		SectorSendBuf(x, y, nullptr);
	}
	serialbuf.clear();
}
void Unicast(CHARACTER* ch)
{
	SendSession(ch->session);
	serialbuf.clear();
}










//
CHARACTER* FindCharacter(DWORD ID)
{
	std::map <DWORD, CHARACTER*>::iterator iter;

	iter = CharacterMap.find(ID);
	if (iter == CharacterMap.end())
		return nullptr;
	else
		return iter->second;
}
CHARACTER* CreateCharacter()
{
	static DWORD ID = 1;
	CHARACTER* ch = new CHARACTER;
	ch->characterID = ID++;
	ch->check = 99999;

	CharacterMap.insert(std::pair<DWORD, CHARACTER*>(ch->characterID, ch));

	return ch;
}
bool DisconnectCharacter(DWORD ID)
{
	CharacterMap.erase(ID);
	return true;
}
CHARACTER* FindID(DWORD sID)
{
	std::map <DWORD, CHARACTER*>::iterator iter;

	iter = SesID_CharMap.find(sID);
	if (SesID_CharMap.end() == iter)
		return 0;
	else
		return iter->second;
}
void CreateID(DWORD sID, CHARACTER* ch)
{
    SesID_CharMap.insert(std::pair<DWORD, CHARACTER*>(sID, ch));
}
bool DisconnectID(DWORD sID)
{
	SesID_CharMap.erase(sID);
	return true;
}




//
void SetCurSector(unsigned short x, unsigned short y, SECTOR_POS* arg)
{
	arg->x = x / SECTOR_X;
	arg->y = y / SECTOR_Y;
}
void GetAround(const SECTOR_POS* pos, SECTOR_AROUND* around)
{
	SECTOR_POS temp;
	around->count = 0;

	temp.x = pos->x;
	temp.y = pos->y;
	around->Around[around->count] = temp;
	around->count++;

	if (pos->x != 0)
	{
		temp.x = pos->x - 1;
		temp.y = pos->y;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->x != (RANGE_MOVE_RIGHT / SECTOR_X))
	{
		temp.x = pos->x + 1;
		temp.y = pos->y;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->y != 0)
	{
		temp.x = pos->x;
		temp.y = pos->y - 1;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->y != (RANGE_MOVE_BOTTOM / SECTOR_Y))
	{
		temp.x = pos->x;
		temp.y = pos->y + 1;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->x != 0 && pos->y != 0)
	{
		temp.x = pos->x - 1;
		temp.y = pos->y - 1;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->x != (RANGE_MOVE_RIGHT / SECTOR_X) && pos->y != (RANGE_MOVE_BOTTOM / SECTOR_Y))
	{
		temp.x = pos->x + 1;
		temp.y = pos->y + 1;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->x != 0 && pos->y != (RANGE_MOVE_BOTTOM / SECTOR_Y))
	{
		temp.x = pos->x - 1;
		temp.y = pos->y + 1;
		around->Around[around->count] = temp;
		around->count++;
	}
	if (pos->x != (RANGE_MOVE_RIGHT / SECTOR_X) && pos->y != 0)
	{
		temp.x = pos->x + 1;
		temp.y = pos->y - 1;
		around->Around[around->count] = temp;
		around->count++;
	}
}











//
void AcceptProc()
{
	while (1)
	{
		if (!AcceptQueue.size())
			return;
		SESSION* pSession = AcceptQueue.front(); AcceptQueue.pop();
		if (pSession == nullptr) return;
		

		CHARACTER* ch = CreateCharacter();
		CreateID(pSession->SessionID, ch);
		ch->valid = true;
		ch->session = pSession;
		ch->HP = 100;
		ch->X = rand() % 6400;  ch->Y = rand() % 6400;
		ch->Action = STOP;
		ch->Direction = RR;
		SetCurSector(ch->X, ch->Y, &ch->cur);
		SetCurSector(ch->X, ch->Y, &ch->old);
		Sector[ch->cur.y][ch->cur.x].push_back(ch);




		mpMyCreate(ch->characterID, ch->Direction, ch->X, ch->Y, ch->HP);
		Unicast(ch);

		SECTOR_AROUND around;
		GetAround(&ch->cur, &around);
		for (int i = 0; i < around.count; i++)
		{
			std::list<CHARACTER*>::iterator iter;
			std::list<CHARACTER*>* lst = &(Sector[around.Around[i].y][around.Around[i].x]);
			for (iter = lst->begin(); iter != lst->end(); iter++)
			{
				CHARACTER* iterCH = (*iter);
				if (iterCH == ch)
					continue;

				mpOtherCreate(iterCH->characterID, iterCH->Direction, iterCH->X, iterCH->Y, iterCH->HP);
				Unicast(ch);
				if (iterCH->Action >= LL || iterCH->Action <= DL)
				{
					mpMoveStar(iterCH->characterID, iterCH->Action, iterCH->X, iterCH->Y);
					Unicast(ch);
				}
			}
		}

		mpOtherCreate(ch->characterID, ch->Direction, ch->X, ch->Y, ch->HP);
		CharacterAroundCast(ch, false);
	}


}



//session에 문제가 있는 상태에서 (클라가 recv를 안함(클라가 죽음?, 멈춤?), recv했는데 소켓에러가 뜨는 경우)
//
void DequeProc()
{
	while (1)
	{
		if (!RecvQueue.size())
			return;
		SESSION* pSession = RecvQueue.front(); RecvQueue.pop();
		if (pSession == nullptr) return;
		

		CHARACTER* ch = FindID(pSession->SessionID);
		if (ch == nullptr)
			continue;
		MessageDeque(ch);
	}
}


void MessageDeque(CHARACTER* ch)
{
	RingQueue* Queue = &ch->session->RecvQ;



	mHEADER pHeader;
	int messageSize;
	int messageType;

	int headerSize = sizeof(mHEADER);
	while (1)
	{
		//while 제어문, 큐에 헤더 사이즈만큼 없으면 탈출
		if (Queue->GetUseSize() < headerSize)
			break;



		//헤더 빼기
		int peakVal = Queue->Peek((char*)&pHeader, headerSize);

		
		messageSize = pHeader.bySize;
		messageType = pHeader.byType;

		//while 제어문, 큐에 메세지 사이즈만큼 없으면 탈출
		if (Queue->GetUseSize() < messageSize + headerSize)
			break;


		
		Queue->MoveFront(headerSize);
		Queue->Dequeue(serialbuf.getBufferPtr(), messageSize);
		serialbuf.moveRear(messageSize);

		
		MessageCall(messageType, ch);
	}
}
void MessageCall(int messageType, CHARACTER* ch)
{
	switch (messageType)
	{
	case dfPACKET_CS_MOVE_START:
		MoveCall(ch);
		break;
	case dfPACKET_CS_MOVE_STOP:
		StopCall(ch);
		break;
	case dfPACKET_CS_ATTACK1:
		Attack1Call(ch);
		break;
	case dfPACKET_CS_ATTACK2:
		Attack2Call(ch);
		break;
	case dfPACKET_CS_ATTACK3:
		Attack3Call(ch);
		break;
	case dfPACKET_CS_ECHO:
		EchoCall(ch);
		break;
	}
}
void MoveCall(CHARACTER* ch)
{
	unsigned char Action;
	unsigned short X;
	unsigned short Y;
	int size = sizeof(Action) + sizeof(X) + sizeof(Y);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Action;
	serialbuf >> X;
	serialbuf >> Y;
	serialbuf.clear();


	MoveProc_Content(Action, X, Y, ch);
}
void StopCall(CHARACTER* ch)
{
	unsigned char Direction;
	unsigned short X;
	unsigned short Y;
	int size = sizeof(Direction) + sizeof(X) + sizeof(Y);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Direction;
	serialbuf >> X;
	serialbuf >> Y;
	serialbuf.clear();


	StopProc_Content(Direction, X, Y, ch);
}
void EchoCall(CHARACTER* ch)
{
	unsigned int Time;
	int size = sizeof(Time);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Time;
	serialbuf.clear();


	EchoProc_Content(Time, ch);
}
void Attack1Call(CHARACTER* ch)
{
	unsigned char Direction;
	unsigned short X;
	unsigned short Y;
	int size = sizeof(Direction) + sizeof(X) + sizeof(Y);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Direction;
	serialbuf >> X;
	serialbuf >> Y;
	serialbuf.clear();


	Attack1Proc_Content(Direction, X, Y, ch);
}
void Attack2Call(CHARACTER* ch)
{
	unsigned char Direction;
	unsigned short X;
	unsigned short Y;
	int size = sizeof(Direction) + sizeof(X) + sizeof(Y);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Direction;
	serialbuf >> X;
	serialbuf >> Y;
	serialbuf.clear();


	Attack1Proc_Content(Direction, X, Y, ch);
}
void Attack3Call(CHARACTER* ch)
{
	unsigned char Direction;
	unsigned short X;
	unsigned short Y;
	int size = sizeof(Direction) + sizeof(X) + sizeof(Y);
	if (size != serialbuf.useSize())
	{
		//로깅
		printf("패킷 손상");
		serialbuf.clear();
		ch->valid = false;
		return;
	}
	serialbuf >> Direction;
	serialbuf >> X;
	serialbuf >> Y;
	serialbuf.clear();


	Attack1Proc_Content(Direction, X, Y, ch);
}
			
//
void MoveProc_Content(unsigned char Action, unsigned short X, unsigned short Y, CHARACTER* ch)
{
	unsigned char prev = ch->Action;
	int prevX = ch->X; int prevY = ch->Y;
	ch->X = X; ch->Y = Y; ch->Action = Action;
	if (abs((ch->X - prevX)) > ERROR_RANGE || abs((ch->Y - prevY)) > ERROR_RANGE)
	{
		ch->X = prevX;
		ch->Y = prevY;
 		mpSYNC(ch->characterID, ch->X, ch->Y);
		CharacterAroundCast(ch, true);
	}

	mpMoveStar(ch->characterID, ch->Action, ch->X, ch->Y);
	CharacterAroundCast(ch, false);
}
void StopProc_Content(unsigned char Direction, unsigned short X, unsigned short Y, CHARACTER* ch)
{
	unsigned char prev = ch->Action;
	int prevX = ch->X; int prevY = ch->Y;
	ch->X = X; ch->Y = Y; ch->Direction = Direction; ch->Action = STOP;
	if (abs((ch->X - prevX)) > ERROR_RANGE || abs((ch->Y - prevY)) > ERROR_RANGE)
	{
		ch->X = prevX;
		ch->Y = prevY;
		mpSYNC(ch->characterID, ch->X, ch->Y);
		CharacterAroundCast(ch, true);
	}

	mpMoveStop(ch->characterID, ch->Direction, ch->X, ch->Y);
	CharacterAroundCast(ch, false);
}
void Attack1Proc_Content(unsigned char Direction, unsigned short X, unsigned short Y, CHARACTER* ch)
{
	int prevX = ch->X; int prevY = ch->Y;
	ch->X = X; ch->Y = Y; ch->Direction = Direction; ch->Action = STOP;
	if (abs((ch->X - prevX)) > ERROR_RANGE || abs((ch->Y - prevY)) > ERROR_RANGE)
	{
		ch->X = prevX;
		ch->Y = prevY;
		mpSYNC(ch->characterID, ch->X, ch->Y);
		CharacterAroundCast(ch, true);
	}

	mpAttack1(ch->characterID, ch->Direction, ch->X, ch->Y);
	CharacterAroundCast(ch);



	int damageVal = 1;


	unsigned int startY;
	unsigned int endY;
	
	if (ch->Y + ATTACK1_RANGE_Y > RANGE_MOVE_BOTTOM)
		startY = RANGE_MOVE_BOTTOM;
	else
		startY = ch->Y + ATTACK1_RANGE_Y;

	if (ch->Y  > ATTACK1_RANGE_Y)
		endY = ch->Y - ATTACK1_RANGE_Y;
	else
		endY = RANGE_MOVE_TOP;

	unsigned int startX;
	unsigned int endX;
	if (ch->Direction == LL)
	{
		if (ch->X > 10)
			startX = ch->X - 10;
		else
			startX = RANGE_MOVE_LEFT;

		if (ch->X > ATTACK1_RANGE_X)
			endX = ch->X - ATTACK1_RANGE_X;
		else
			endX = RANGE_MOVE_LEFT;
	}
	else
	{
		if (ch->X + 10 > RANGE_MOVE_RIGHT)
			startX = RANGE_MOVE_RIGHT;
		else
			startX = ch->X + 10;

		if (ch->X + ATTACK1_RANGE_X > RANGE_MOVE_RIGHT)
			endX = RANGE_MOVE_RIGHT;
		else
			endX = ch->X + ATTACK1_RANGE_X;
	}

	SECTOR_POS HitSector1;
	SECTOR_POS HitSector2;
	SetCurSector(startX, startY, &HitSector1);
	SetCurSector(endX, endY, &HitSector2);

	std::list<CHARACTER*>::iterator iter;
	std::list<CHARACTER*>* lst = &Sector[HitSector1.y][HitSector1.x];
	for (iter = lst->begin(); iter != lst->end(); iter++)
	{
		CHARACTER* p = (*iter);
		if (p->Y < endY || p->Y >startY)
			continue;

		if (ch->Direction == LL)
		{
			if (p->X > startX || p->X < endX)
				continue;
		}
		else
		{
			if (p->X < startX || p->X > endX)
				continue;
		}
		p->HP = p->HP - damageVal;


		mpDamage(ch->characterID, p->characterID, p->HP);
		CharacterAroundCast(p, true);
	}

	if (HitSector1.x == HitSector2.x && HitSector2.y == HitSector2.y)
		return;


	lst = &Sector[HitSector2.y][HitSector2.x];
	for (iter = lst->begin(); iter != lst->end(); iter++)
	{
		CHARACTER* p = (*iter);
		if (p->Y < endY || p->Y >startY)
			continue;

		if (p->Direction == LL)
		{
			if ((*iter)->X > startX || (*iter)->X < endX)
				continue;
		}
		else
		{
			if ((*iter)->X < startX || (*iter)->X > endX)
				continue;
		}
		(*iter)->HP = (*iter)->HP - damageVal;


		mpDamage(ch->characterID, p->characterID, p->HP);
		CharacterAroundCast(p, true);
	}
}
void EchoProc_Content(unsigned int Time, CHARACTER* ch)
{
	mpEcho(Time);
	Unicast(ch);
}







//
void Update()
{
	static DWORD prevTime = timeGetTime();
	static DWORD curTime;
	curTime = timeGetTime();
	DWORD delta = (curTime - prevTime);
	if (delta < 40)
		return;
	
	prevTime = timeGetTime();
	prevTime = prevTime - delta + 40;
	

	

	CHARACTER* ch;
	std::map <DWORD, CHARACTER*>::iterator iter;
	int c = 0;
	for (iter = CharacterMap.begin(); iter != CharacterMap.end(); iter++)
	{
		c++;
		ch = iter->second;

		if (ch->HP <= 0)
		{
			ch->valid = false;
		}

		DWORD t = timeGetTime();
		if (t - (ch->session->LastRecvTime) > 30000)
		{
			ch->valid = false;
		}
		

		if (ch->Action >= LL && ch->Action <= DL)
		{
			MoveLogic(ch);
			SectorChange(ch);
		}
	}

	
}
void MoveLogic(CHARACTER* ch)
{
	if (ch->X < RANGE_MOVE_LEFT)
		return;
	if (ch->X > RANGE_MOVE_RIGHT)
		return;
	if (ch->Y < RANGE_MOVE_TOP)
		return;
	if (ch->Y > RANGE_MOVE_BOTTOM)
		return;

	switch (ch->Action)
	{
	case LL:
		if (ch->X < 6)
			ch->X = 0;
		else
			ch->X = ch->X - 6;
		break;
	case LU:
		if (ch->Y == 0 || ch->X ==0)
			break;

		if (ch->X < 6)
			ch->X = 0;
		else
			ch->X = ch->X - 6;

		if (ch->Y < 4)
			ch->Y = 0;
		else
			ch->Y = ch->Y - 4;
		break;
	case UU:
		if (ch->Y < 4)
			ch->Y = 0;
		else
			ch->Y = ch->Y - 4;
		break;
	case UR:
		if (ch->Y == 0 || ch->X == RANGE_MOVE_RIGHT)
			break;

		if (ch->Y < 4)
			ch->Y = 0;
		else
			ch->Y = ch->Y - 4;

		if (ch->X + 6 > RANGE_MOVE_RIGHT)
			ch->X = RANGE_MOVE_RIGHT;
		else
			ch->X = ch->X + 6;
		break;
	case RR:

		if (ch->X + 6 > RANGE_MOVE_RIGHT)
			ch->X = RANGE_MOVE_RIGHT;
		else
			ch->X = ch->X + 6;
		break;
	case RD:
		if (ch->Y == RANGE_MOVE_BOTTOM || ch->X == RANGE_MOVE_RIGHT)
			break;

		if (ch->X + 6 > RANGE_MOVE_RIGHT)
			ch->X = RANGE_MOVE_RIGHT;
		else
			ch->X = ch->X + 6;

		if (ch->Y + 4 > RANGE_MOVE_BOTTOM)
			ch->Y = RANGE_MOVE_BOTTOM;
		else
			ch->Y = ch->Y + 4;

		break;
	case DD:
		if (ch->Y + 4 > RANGE_MOVE_BOTTOM)
			ch->Y = RANGE_MOVE_BOTTOM;
		else
			ch->Y = ch->Y + 4;
		break;
	case DL:
		if (ch->Y == RANGE_MOVE_BOTTOM || ch->X == 0)
			break;

		if (ch->X < 6)
			ch->X = 0;
		else
			ch->X = ch->X - 6;
		
		if (ch->Y + 4 > RANGE_MOVE_BOTTOM)
			ch->Y = RANGE_MOVE_BOTTOM;
		else
			ch->Y = ch->Y + 4;

		break;
	}
}
void SectorChange(CHARACTER* ch)
{
	ch->old = ch->cur;
	SetCurSector(ch->X, ch->Y, &ch->cur);

	bool flag;
	if ((ch->old.x == ch->cur.x) && (ch->old.y == ch->cur.y))
	{
		flag = false;
	}
	else
	{
		flag = true;
	}

	if (flag)
	{
		std::list<CHARACTER*>::iterator iter;
		std::list<CHARACTER*>* lst = &(Sector[ch->old.y][ch->old.x]);
		for (iter = lst->begin(); iter != lst->end(); iter++)
		{

			if ((*iter) == ch)
			{
				lst->erase(iter);
				break;
			}
		}
		Sector[ch->cur.y][ch->cur.x].push_back(ch);

		//
		SECTOR_AROUND old;
		SECTOR_AROUND cur;
		SECTOR_AROUND add;
		SECTOR_AROUND remove;

		//
		GetAround(&ch->old, &old);
		GetAround(&ch->cur, &cur);
		add.count = 0;
		for (int i = 0; i < cur.count; i++)
		{
			bool chaeck = true;
			for (int j = 0; j < old.count; j++)
			{
				if ((old.Around[j].x == cur.Around[i].x) && (old.Around[j].y == cur.Around[i].y))
					chaeck = false;
			}
			if (chaeck)
			{
				add.Around[add.count++] = cur.Around[i];
			}
		}
		remove.count = 0;
		for (int i = 0; i < old.count; i++)
		{
			bool chaeck = true;
			for (int j = 0; j < cur.count; j++)
			{
				if ((old.Around[i].x == cur.Around[j].x) && (old.Around[i].y == cur.Around[j].y))
					chaeck = false;
			}
			if (chaeck)
			{
				remove.Around[remove.count++] = old.Around[i];
			}
		}

		//
		mpDelete(ch->characterID);
		SpecificSectorsCast(&remove);

		for (int i = 0; i < remove.count; i++)
		{
			std::list<CHARACTER*>::iterator iter;
			std::list<CHARACTER*>* lst = &Sector[remove.Around[i].y][remove.Around[i].x];
			for (iter = lst->begin(); iter != lst->end(); iter++)
			{
				mpDelete((*iter)->characterID);
				Unicast(ch);
			}
		}
		mpOtherCreate(ch->characterID, ch->Direction, ch->X, ch->Y, ch->HP);
		SpecificSectorsCast(&add);


		mpMoveStar(ch->characterID, ch->Action, ch->X, ch->Y);
		SpecificSectorsCast(&add);


		for (int i = 0; i < add.count; i++)
		{
			std::list<CHARACTER*>::iterator iter;
			std::list<CHARACTER*>* lst = &Sector[add.Around[i].y][add.Around[i].x];
			for (iter = lst->begin(); iter != lst->end(); iter++)
			{
				CHARACTER* iterCH = (*iter);
				if (iterCH == ch)
					continue;
				

				mpOtherCreate(iterCH->characterID, iterCH->Direction, iterCH->X, iterCH->Y, iterCH->HP);
				Unicast(ch);
				if (iterCH->Action >= LL || iterCH->Action <= DL)
				{
					mpMoveStar(iterCH->characterID, iterCH->Action, iterCH->X, iterCH->Y);
					Unicast(ch);
				}
			}
		}
	}
}





void DeleteProc()
{
	std::map <DWORD, CHARACTER*>::iterator iter;
	std::map <DWORD, CHARACTER*>::iterator del;
	int count = 0;
	for (iter = CharacterMap.begin(); iter != CharacterMap.end();)
	{
		count++;
		CHARACTER* p = iter->second;

		del = iter;
		iter++;
		
		if (p->valid == false || p->session->Valid == false)
		{
			//로깅
			printf("ch ID - %d, ses ID %d 연결 종료", p->characterID, p->session->SessionID);
			mpDelete(p->characterID);
			CharacterAroundCast(p, true);
			SesID_CharMap.erase(p->session->SessionID);
			SessionMap.erase(p->session->Socket);
			CharacterMap.erase(del);



			std::list<CHARACTER*>::iterator iter2;
			std::list<CHARACTER*>* lst = &(Sector[p->cur.y][p->cur.x]);
			for (iter2 = lst->begin(); iter2 != lst->end(); iter2++)
			{
				if ((*iter2) == p)
				{
					printf("   x : %d // y : %d  delete \n", p->cur.x, p->cur.y);
					lst->erase(iter2);
					break;
				}
			}

			closesocket(p->session->Socket);
			memset(p->session, 0, sizeof(SESSION));
			memset(p, 0, sizeof(CHARACTER));
			free(p->session);
			free(p); 


		}
	}

	
	

}


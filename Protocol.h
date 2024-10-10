/////////////////////////////////////////////////////////////////////
// www.gamecodi.com						������ master@gamecodi.com
//
//
/////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------

��Ŷ������ ����.


�ڽ��� ĳ���Ϳ� ���� ��Ŷ�� �������� ���� ��, ��� �ڽ��� ����
�׼��� ���԰� ���ÿ� ��Ŷ�� ������ �����ֵ��� �Ѵ�.

- �̵� Ű �Է� �� �̵������� ���԰� ���ÿ� �̵� ��Ŷ�� �������� �Ѵ�.
- ����Ű �Է� �� ���� ������ ���ϸ鼭 ��Ŷ�� ������.
- �浹 ó�� �� �������� ���� ������ �������� ó�� �� �뺸�ϰ� �ȴ�.


---------------------------------------------------------------*/
#ifndef __PACKET_DEFINE__
#define __PACKET_DEFINE__

#pragma pack(1)
struct mHEADER
{
	unsigned char 	byCode = 0x89;
	unsigned char 	bySize;
	unsigned char 	byType;
};
//---------------------------------------------------------------
// ��Ŷ���.
//
//---------------------------------------------------------------
/*
	BYTE	byCode;			// ��Ŷ�ڵ� 0x89 ����.
	BYTE	bySize;			// ��Ŷ ������.
	BYTE	byType;			// ��ŶŸ��.
*/





#define	dfPACKET_SC_CREATE_MY_CHARACTER			0
struct mCREATE_MY_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
	unsigned char	HP;
};
//---------------------------------------------------------------
// Ŭ���̾�Ʈ �ڽ��� ĳ���� �Ҵ�		Server -> Client
//
// ������ ���ӽ� ���ʷ� �ްԵǴ� ��Ŷ���� �ڽ��� �Ҵ���� ID ��
// �ڽ��� ���� ��ġ, HP �� �ް� �ȴ�. (ó���� �ѹ� �ް� ��)
// 
// �� ��Ŷ�� ������ �ڽ��� ID,X,Y,HP �� �����ϰ� ĳ���͸� �������Ѿ� �Ѵ�.
//
//	4	-	ID
//	1	-	Direction	(LL / RR)
//	2	-	X
//	2	-	Y
//	1	-	HP
//
//---------------------------------------------------------------








#define	dfPACKET_SC_CREATE_OTHER_CHARACTER		1
struct mCREATE_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
	unsigned char	HP;
};
//---------------------------------------------------------------
// �ٸ� Ŭ���̾�Ʈ�� ĳ���� ���� ��Ŷ		Server -> Client
//
// ó�� ������ ���ӽ� �̹� ���ӵǾ� �ִ� ĳ���͵��� ����
// �Ǵ� �����߿� ���ӵ� Ŭ���̾�Ʈ���� ������ ����.
//
//
//	4	-	ID
//	1	-	Direction	(LL / RR)
//	2	-	X
//	2	-	Y
//	1	-	HP
//
//---------------------------------------------------------------






#define	dfPACKET_SC_DELETE_CHARACTER			2
struct mDELETE_CHARACTER
{
	unsigned int	ID;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ						Server -> Client
//
// ĳ������ �������� �Ǵ� ĳ���Ͱ� �׾����� ���۵�.
//
//	4	-	ID
//
//---------------------------------------------------------------






//down 6
// up 2
// l 0
// r 4
#define	dfPACKET_CS_MOVE_START					10
struct mMOVE_START_MY_CHARACTER
{
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� �̵����� ��Ŷ						Client -> Server
//
// �ڽ��� ĳ���� �̵����۽� �� ��Ŷ�� ������.
// �̵� �߿��� �� ��Ŷ�� ������ ������, Ű �Է��� ����Ǿ��� ��쿡��
// ������� �Ѵ�.
//
// (���� �̵��� ���� �̵� / ���� �̵��� ���� ���� �̵�... ���)
//
//	1	-	Direction	( ���� ������ �� 8���� ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------
#define dfPACKET_MOVE_DIR_LL					0
#define dfPACKET_MOVE_DIR_LU					1
#define dfPACKET_MOVE_DIR_UU					2
#define dfPACKET_MOVE_DIR_RU					3
#define dfPACKET_MOVE_DIR_RR					4
#define dfPACKET_MOVE_DIR_RD					5
#define dfPACKET_MOVE_DIR_DD					6
#define dfPACKET_MOVE_DIR_LD					7
#define dfPACKET_STOP							8
#define LL 0
#define LU 1
#define UU 2
#define UR 3
#define RR 4
#define RD 5
#define DD 6
#define DL 7
#define STOP 8





#define	dfPACKET_SC_MOVE_START					11
struct mMOVE_START_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� �̵����� ��Ŷ						Server -> Client
//
// �ٸ� ������ ĳ���� �̵��� �� ��Ŷ�� �޴´�.
// ��Ŷ ���Ž� �ش� ĳ���͸� ã�� �̵�ó���� ���ֵ��� �Ѵ�.
// 
// ��Ŷ ���� �� �ش� Ű�� ����ؼ� ���������� �����ϰ�
// �ش� �������� ��� �̵��� �ϰ� �־�߸� �Ѵ�.
//
//	4	-	ID
//	1	-	Direction	( ���� ������ �� 8���� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------



#define	dfPACKET_CS_MOVE_STOP					12
struct mMOVE_STOP_MY_CHARACTER
{
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
// ĳ���� �̵����� ��Ŷ						Client -> Server
//
// �̵��� Ű���� �Է��� ��� �����Ǿ��� ��, �� ��Ŷ�� ������ �����ش�.
// �̵��� ���� ��ȯ�ÿ��� ��ž�� ������ �ʴ´�.
//
//	1	-	Direction	( ���� ������ �� ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------




#define	dfPACKET_SC_MOVE_STOP					13
struct mMOVE_STOP_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� �̵����� ��Ŷ						Server -> Client
//
// ID �� �ش��ϴ� ĳ���Ͱ� �̵��� ������̹Ƿ� 
// ĳ���͸� ã�Ƽ� �����, ��ǥ�� �Է����ְ� ���ߵ��� ó���Ѵ�.
//
//	4	-	ID
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------



#define	dfPACKET_CS_ATTACK1						20
struct mATTACK1_MY_CHARACTER
{
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Client -> Server
//
// ���� Ű �Է½� �� ��Ŷ�� �������� ������.
// �浹 �� �������� ���� ����� �������� �˷� �� ���̴�.
//
// ���� ���� ���۽� �ѹ��� �������� ������� �Ѵ�.
//
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y	
//
//---------------------------------------------------------------





#define	dfPACKET_SC_ATTACK1						21
struct mATTACK1_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Server -> Client
//
// ��Ŷ ���Ž� �ش� ĳ���͸� ã�Ƽ� ����1�� �������� �׼��� �����ش�.
// ������ �ٸ� ��쿡�� �ش� �������� �ٲ� �� ���ش�.
//
//	4	-	ID
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------


#define	dfPACKET_CS_ATTACK2						22
struct mATTACK2_MY_CHARACTER
{
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Client -> Server
//
// ���� Ű �Է½� �� ��Ŷ�� �������� ������.
// �浹 �� �������� ���� ����� �������� �˷� �� ���̴�.
//
// ���� ���� ���۽� �ѹ��� �������� ������� �Ѵ�.
//
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------

#define	dfPACKET_SC_ATTACK2						23
struct mATTACK2_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Server -> Client
//
// ��Ŷ ���Ž� �ش� ĳ���͸� ã�Ƽ� ����2�� �������� �׼��� �����ش�.
// ������ �ٸ� ��쿡�� �ش� �������� �ٲ� �� ���ش�.
//
//	4	-	ID
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------

#define	dfPACKET_CS_ATTACK3						24
struct mATTACK3_MY_CHARACTER
{
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Client -> Server
//
// ���� Ű �Է½� �� ��Ŷ�� �������� ������.
// �浹 �� �������� ���� ����� �������� �˷� �� ���̴�.
//
// ���� ���� ���۽� �ѹ��� �������� ������� �Ѵ�.
//
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------

#define	dfPACKET_SC_ATTACK3						25
struct mATTACK3_OTHER_CHARACTER
{
	unsigned int	ID;
	unsigned char	Direction;
	unsigned short	X;
	unsigned short	Y;
};
//---------------------------------------------------------------
// ĳ���� ���� ��Ŷ							Server -> Client
//
// ��Ŷ ���Ž� �ش� ĳ���͸� ã�Ƽ� ����3�� �������� �׼��� �����ش�.
// ������ �ٸ� ��쿡�� �ش� �������� �ٲ� �� ���ش�.
//
//	4	-	ID
//	1	-	Direction	( ���� ������ ��. ��/�츸 ��� )
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------





#define	dfPACKET_SC_DAMAGE						30
struct mSC_DAMAGE
{
	unsigned int	AttackID;
	unsigned int	DamageID;
	unsigned char	DamageHP;
};
//---------------------------------------------------------------
// ĳ���� ������ ��Ŷ							Server -> Client
//
// ���ݿ� ���� ĳ������ ������ ����.
//
//	4	-	AttackID	( ������ ID )
//	4	-	DamageID	( ������ ID )
//	1	-	DamageHP	( ������ HP )
//
//---------------------------------------------------------------








// ������...
#define	dfPACKET_CS_SYNC						250
struct mCS_SYNC
{
	unsigned short X;
	unsigned short Y;
};
//---------------------------------------------------------------
// ����ȭ�� ���� ��Ŷ					Client -> Server
//
//
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------


#define	dfPACKET_SC_SYNC						251
struct m_SYNC
{
	unsigned int ID;
	unsigned short X;
	unsigned short Y;
};
//---------------------------------------------------------------
// ����ȭ�� ���� ��Ŷ					Server -> Client
//
// �����κ��� ����ȭ ��Ŷ�� ������ �ش� ĳ���͸� ã�Ƽ�
// ĳ���� ��ǥ�� �������ش�.
//
//	4	-	ID
//	2	-	X
//	2	-	Y
//
//---------------------------------------------------------------


#define	dfPACKET_CS_ECHO						252
//---------------------------------------------------------------
// Echo �� ��Ŷ					Client -> Server
//
//	4	-	Time
//
//---------------------------------------------------------------
struct m_CS_ECHO
{
	unsigned int Time;
};
#define	dfPACKET_SC_ECHO						253
//---------------------------------------------------------------
// Echo ���� ��Ŷ				Server -> Client
//
//	4	-	Time
//
//---------------------------------------------------------------
struct m_SC_ECHO
{
	unsigned int Time;
};


#pragma pack(8)
#endif


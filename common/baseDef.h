#pragma once
#include "../my_iocp/stdafx.h"


/* ������л�������Ϣ����ض���
   create 20170523
   by	  blackE
*/

#define		MAX_MSG_LENGTH		1024 * 4			// ��Ϣ����󳤶�
#define		MAX_CHAT_LENGTH		1024				// ������Ϣ��󳤶�
#define		MAX_THREAD_NUM		8					// �̳߳��߳���
#define		MAX_BUFFER_LEN		1024 * 4			// ����������
#define		MAX_BASEMSG_LEN		4100				// base����
#define		MAX_ACCEPTDATA_LEN	500					// �������Ӻ󷵻ص�hello data + srvAddr + clientAddr

//CRITICAL_SECTION CSMAP_USERID_SOCK;		// ����map_UserID_Sock�ٽ���



// �߼���Ϣ��
#define		MSG_ECHO		0x00000000			// У����Ϣ
#define		MSG_CHAT		0x00000001			// ������Ϣ
//////////////////////////////////////////////////////////////
// ������Ϣ��������Ϣ����װ��������з���
typedef struct _BASEMSG
{
	int		nMsgNO;			// ��Ϣ��
	char	MsgData[MAX_MSG_LENGTH];		// ��Ϣ��
}BASEMSG, *pBASEMSG;

// ������Ϣ
typedef struct _CHATMSG
{
	int		nDestUserID;							// ������Ϣ���û�ID
	char	ChatData[MAX_CHAT_LENGTH];				// ��������
}CHATMSG, *pCHATMSG;
			

enum OPERATION_TYPE
{
	OPE_ACCEPT = 1,
	OPE_RECV,
	OPE_SEND
};

typedef struct _PER_IO_CONTEXT
{
	OVERLAPPED	 Overlapped;				// �ص�IO
	SOCKET		 SockAccept;				// IO������Ӧ��socket
	WSABUF		 WsaBuf;					// ���ݻ�����
	char		 sz_Buffer[MAX_BASEMSG_LEN];	// ��ӦWsaBuf��������
	int			 sz_bufLen;					// ʵ�����ݳ���
	OPERATION_TYPE OpeType;					// IO��������
}PER_IO_CONTEXT, *pPER_IO_CONTEXT;

typedef struct _PER_SOCKET_CONTEXT
{
	PER_IO_CONTEXT*		pIOContent;			// io������
	SOCKET			Socket;					// ÿ���ͻ��˵�socket
	//SOCKADDR_IN		ClientAddr;				// �ͻ��˵�ַ
	//CArray<PER_IO_CONTEXT*> Array;			// ���飬���Կͻ���IO����
}PER_SOCKET_CONTEXT, *pPER_SOCKET_CONTEXT;

// AcceptEx���buf
typedef struct _ACCEPT_OUT_BUFFER
{
	char		OutInfo[MAX_MSG_LENGTH];		// ��������ʱ�յ�������
	SOCKADDR	SockAddr_Server;				// ���ص�ַ
	SOCKADDR	SockAddr_Client;				// �ͻ��˵�ַ
}ACCEPT_OUT_BUFFER, *pACCEPT_OUT_BUFFER;

// У��str
typedef struct _HELLODATA
{
	int nUserID;
	char HelloStr[MAX_CHAT_LENGTH];
}HELLODATA, *pHELLODATA;
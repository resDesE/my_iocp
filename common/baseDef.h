#pragma once
#include "../my_iocp/stdafx.h"


/* 这里进行基础的消息等相关定义
   create 20170523
   by	  blackE
*/

#define		MAX_MSG_LENGTH		1024 * 4			// 消息体最大长度
#define		MAX_CHAT_LENGTH		1024				// 聊天消息最大长度
#define		MAX_THREAD_NUM		8					// 线程池线程数
#define		MAX_BUFFER_LEN		1024 * 4			// 缓冲区长度
#define		MAX_BASEMSG_LEN		4100				// base长度
#define		MAX_ACCEPTDATA_LEN	500					// 接受连接后返回的hello data + srvAddr + clientAddr

//CRITICAL_SECTION CSMAP_USERID_SOCK;		// 遍历map_UserID_Sock临界区



// 逻辑消息号
#define		MSG_ECHO		0x00000000			// 校验消息
#define		MSG_CHAT		0x00000001			// 聊天消息
//////////////////////////////////////////////////////////////
// 基础消息，其他消息均需装入这里进行发送
typedef struct _BASEMSG
{
	int		nMsgNO;			// 消息号
	char	MsgData[MAX_MSG_LENGTH];		// 消息体
}BASEMSG, *pBASEMSG;

// 聊天消息
typedef struct _CHATMSG
{
	int		nDestUserID;							// 接收消息的用户ID
	char	ChatData[MAX_CHAT_LENGTH];				// 聊天内容
}CHATMSG, *pCHATMSG;
			

enum OPERATION_TYPE
{
	OPE_ACCEPT = 1,
	OPE_RECV,
	OPE_SEND
};

typedef struct _PER_IO_CONTEXT
{
	OVERLAPPED	 Overlapped;				// 重叠IO
	SOCKET		 SockAccept;				// IO操作对应的socket
	WSABUF		 WsaBuf;					// 数据缓冲区
	char		 sz_Buffer[MAX_BASEMSG_LEN];	// 对应WsaBuf的数据区
	int			 sz_bufLen;					// 实际数据长度
	OPERATION_TYPE OpeType;					// IO操作类型
}PER_IO_CONTEXT, *pPER_IO_CONTEXT;

typedef struct _PER_SOCKET_CONTEXT
{
	PER_IO_CONTEXT*		pIOContent;			// io上下文
	SOCKET			Socket;					// 每个客户端的socket
	//SOCKADDR_IN		ClientAddr;				// 客户端地址
	//CArray<PER_IO_CONTEXT*> Array;			// 数组，所以客户端IO操作
}PER_SOCKET_CONTEXT, *pPER_SOCKET_CONTEXT;

// AcceptEx输出buf
typedef struct _ACCEPT_OUT_BUFFER
{
	char		OutInfo[MAX_MSG_LENGTH];		// 接受连接时收到的数据
	SOCKADDR	SockAddr_Server;				// 本地地址
	SOCKADDR	SockAddr_Client;				// 客户端地址
}ACCEPT_OUT_BUFFER, *pACCEPT_OUT_BUFFER;

// 校验str
typedef struct _HELLODATA
{
	int nUserID;
	char HelloStr[MAX_CHAT_LENGTH];
}HELLODATA, *pHELLODATA;
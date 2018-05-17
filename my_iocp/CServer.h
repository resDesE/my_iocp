/* 服务器类定义，使用iocp模型进行线程和
***socket管理
   create 20170523
   by	  blackE
*/

#pragma once

#include "stdafx.h"


class CServer
{
public:
	CServer();
	~CServer();
	bool Run();					// 服务器开始
private:
	bool CreateThreads();		// 构建线程池
public:
	bool StartAcceptEx();		// 开始异步接受连接请求

	int OnAcceptClient(pPER_SOCKET_CONTEXT lpPerSocketContext);	// 接受连接

	int OnSendDataMsg(PER_IO_CONTEXT* pIoContent);	// 数据发送

	int OnRecvDataMsg(PER_IO_CONTEXT* pIoContent);	// 数据读取成功
public:
	SOCKET m_ListenSocket;
	HANDLE m_IoCompletionPort;		// IO完成端口
	HANDLE* m_pWorkThread;			// 线程池
	//static std::map <SOCKET, pPER_SOCKET_CONTEXT> _CurrentCon;	// 记录当前连接
};

/* �������ඨ�壬ʹ��iocpģ�ͽ����̺߳�
***socket����
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
	bool Run();					// ��������ʼ
private:
	bool CreateThreads();		// �����̳߳�
public:
	bool StartAcceptEx();		// ��ʼ�첽������������

	int OnAcceptClient(pPER_SOCKET_CONTEXT lpPerSocketContext);	// ��������

	int OnSendDataMsg(PER_IO_CONTEXT* pIoContent);	// ���ݷ���

	int OnRecvDataMsg(PER_IO_CONTEXT* pIoContent);	// ���ݶ�ȡ�ɹ�
public:
	SOCKET m_ListenSocket;
	HANDLE m_IoCompletionPort;		// IO��ɶ˿�
	HANDLE* m_pWorkThread;			// �̳߳�
	//static std::map <SOCKET, pPER_SOCKET_CONTEXT> _CurrentCon;	// ��¼��ǰ����
};

// my_iocp.cpp : �������̨Ӧ�ó������ڵ㡣
//
#pragma once

#include "stdafx.h"
#include "CServer.h"
#include <string>
#include <iostream>
//#include "CServerControl.h"
#include <map>
#include "CSession.h"
#include "CSessionMgr.h"

int g_BaseID = 0;
//std::map <SOCKET, pPER_SOCKET_CONTEXT> g_CurrentCon;


int g_nCurrentUserCount = 0;

unsigned _stdcall ThreadPrc(PVOID Param)
{
	CServer* pServer = (CServer*)Param;
	HANDLE ComlPort = pServer->m_IoCompletionPort;
	while (true)
	{
		unsigned long long ullClientContent = 0;	// �����ݾ��
		pPER_SOCKET_CONTEXT lpPerSocketContext = NULL;
		pPER_IO_CONTEXT lpPerIoContext = NULL;				// ��IO���
		DWORD dwBytesTransfered = 0;
		BOOL bRet = FALSE;
		DWORD	RecvBytes = 0;
		DWORD	Flags = 0;

		dwBytesTransfered = 0;
		char newBuf[MAX_BASEMSG_LEN] = {0};
		// �̲߳��ϵش�Queue��������ɵ�io������queue��Windows�Զ�����ά��
		bRet = GetQueuedCompletionStatus(ComlPort, &dwBytesTransfered, (unsigned long long*)&ullClientContent, (LPOVERLAPPED*)&lpPerIoContext, INFINITE);
		if (bRet)
		{
			if (NULL == ullClientContent)
			{
				lpPerSocketContext = (pPER_SOCKET_CONTEXT)GlobalAlloc(GPTR, sizeof(PER_SOCKET_CONTEXT));
				lpPerSocketContext->pIOContent = lpPerIoContext;
			}
			else
			{
				lpPerSocketContext = (pPER_SOCKET_CONTEXT)ullClientContent;
			}
		}
		else
		{
			std::cout << "GetQueuedCompletionStatus ret false, err = " << GetLastError() << std::endl;
			continue;
		}
		// �����ܵ������Ƿ���ȷ
		if (dwBytesTransfered == 0 && (lpPerSocketContext->pIOContent->OpeType == OPE_RECV
			|| lpPerSocketContext->pIOContent->OpeType == OPE_SEND))
		{
			closesocket(lpPerSocketContext->pIOContent->SockAccept);
			/*GlobalFree(lpPerIoContext);
			GlobalFree(lpPerSocketContext);*/
			std::cout << "func ThreadPrc Accept Error, thrad id :"
				<< GetCurrentThreadId() << std::endl;
		}

		// �����������
		if (lpPerSocketContext->pIOContent->OpeType == OPE_ACCEPT)
		{
			// ץ��ʱ��Ͷ���¸�����
			pServer->StartAcceptEx();

			pServer->OnAcceptClient(lpPerSocketContext);

		}
		// ���ݽ������
		if (lpPerSocketContext->pIOContent->OpeType == OPE_RECV)
		{
			pServer->OnRecvDataMsg(lpPerSocketContext->pIOContent);
			// ÿ�ν�������ٴ�Ͷ��һ�����ղ���,��ʵ�ֳ����Ľ���
			memset(&(lpPerSocketContext->pIOContent->Overlapped), 0, sizeof(OVERLAPPED));
			if (WSARecv(lpPerSocketContext->pIOContent->SockAccept, &(lpPerSocketContext->pIOContent->WsaBuf), 1,
				&RecvBytes, &Flags, &(lpPerSocketContext->pIOContent->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSA_IO_PENDING)
				{
					std::cout << "func WSARecv recving data len : " << RecvBytes << std::endl;
				}
				continue;
			}
			
		}
		// ���ݷ������
		if (lpPerSocketContext->pIOContent->OpeType == OPE_SEND)
		{
			pServer->OnSendDataMsg(lpPerSocketContext->pIOContent);
		}
		Flags = 0;

	}
	return 0;
}


CServer::CServer()
{
	m_IoCompletionPort = INVALID_HANDLE_VALUE;
	m_ListenSocket = INVALID_SOCKET;
	m_pWorkThread = NULL;
}

CServer::~CServer()
{
	if (INVALID_SOCKET != m_ListenSocket)
	{
		closesocket(m_ListenSocket);
		m_ListenSocket = INVALID_SOCKET;
	}

	if (INVALID_HANDLE_VALUE != m_IoCompletionPort)
	{
		CloseHandle(m_IoCompletionPort);
		m_IoCompletionPort = INVALID_HANDLE_VALUE;
	}
}

bool CServer::Run()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	m_IoCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// ��ʼ������socket
	m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		printf_s("func run Create listen socket ERROR!");
		return false;
	}
	// ����socket��ַ�˿�
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(7777);
	// ��socket����ַ�˿���
	if (SOCKET_ERROR == bind(m_ListenSocket, (SOCKADDR *)&addr, sizeof(addr)))
	{
		printf("func run bind ERROR!");
		return false;
	}
	// ��ʼsocket����
	if (0 != listen(m_ListenSocket, SOMAXCONN))
	{
		printf("func run socket ��������!");
		return false;
	}

	/*pPER_IO_CONTEXT PerIoContext;
	PerIoContext = (pPER_IO_CONTEXT)GlobalAlloc(GPTR, sizeof(PER_IO_CONTEXT));
	PerIoContext->SockAccept = m_ListenSocket;*/
	CreateIoCompletionPort((HANDLE*)m_ListenSocket, m_IoCompletionPort, /*(DWORD)PerIoContext*/0, 0);

	StartAcceptEx();
	CreateThreads();
	return true;
}

bool CServer::StartAcceptEx()
{
	pPER_IO_CONTEXT pIOContent = (pPER_IO_CONTEXT)GlobalAlloc(GPTR, sizeof(PER_IO_CONTEXT));
	memset(&(pIOContent->Overlapped), 0, sizeof(OVERLAPPED));
	pIOContent->OpeType = OPE_ACCEPT;
	pIOContent->SockAccept = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	pIOContent->sz_bufLen = MAX_ACCEPTDATA_LEN;
	DWORD RevDataLen = 0;

	int rt =AcceptEx(m_ListenSocket,
		pIOContent->SockAccept,
		pIOContent->sz_Buffer,
					/*PerIoContext->sz_bufLen - (sizeof(sockaddr_in) + 16) * 2*/0,
					sizeof(sockaddr_in) + 16,
					sizeof(sockaddr_in) + 16,
					&RevDataLen,
					&(pIOContent->Overlapped));
	if (rt == FALSE)
	{
		int error = WSAGetLastError();
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			std::cout << "func AcceptEx ERROR!" << std::endl;
		}
		else
		{
			std::cout << "Server wiating accept..." << std::endl;
		}
			
	}
	return true;
}

int CServer::OnSendDataMsg(PER_IO_CONTEXT* pIoContent)
{
	// ��ʾ�����ֽ���
	std::cout << "Send succ, send Data: " << pIoContent->sz_bufLen << " B" << std::endl;
	return 0;
}

int CServer::OnRecvDataMsg(PER_IO_CONTEXT* pIoContent)
{
	if (nullptr == pIoContent)
	{
		return 0;
	}
	// �����׸�session�Լ��ڲ�����
	CSession* pSession = CSessionMgr::Instance()->OnGetSessionBySock(pIoContent->SockAccept);
	if (nullptr != pSession)
	{
		return pSession->OnReqest(pIoContent);
	}
	return 0;
}

int CServer::OnAcceptClient(pPER_SOCKET_CONTEXT lpPerSocketContext)
{
	if (setsockopt(lpPerSocketContext->pIOContent->SockAccept, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
		(char*)&(lpPerSocketContext->pIOContent->SockAccept), sizeof(lpPerSocketContext->pIOContent->SockAccept)) == SOCKET_ERROR)
	{
		std::cout << "func ThreadPrc setsocket waiting..." << std::endl;
	}
	lpPerSocketContext->Socket = lpPerSocketContext->pIOContent->SockAccept;

	// ���������ӵ�socket����ɶ˿�
	CreateIoCompletionPort((HANDLE)lpPerSocketContext->Socket, m_IoCompletionPort, (ULONG_PTR)lpPerSocketContext, 0);
	//memset(&(lpPerSocketContext->ioContent.Overlapped), 0, sizeof(OVERLAPPED));
	lpPerSocketContext->pIOContent->OpeType = OPE_RECV;			// �ͻ��˷�����������󣬿�ʼ���տͻ�������
	// ����WSABUF�ṹ
	lpPerSocketContext->pIOContent->sz_bufLen = MAX_BASEMSG_LEN;
	lpPerSocketContext->pIOContent->WsaBuf.buf = lpPerSocketContext->pIOContent->sz_Buffer;
	lpPerSocketContext->pIOContent->WsaBuf.len = MAX_BASEMSG_LEN;

	// ����session
	CSessionMgr::Instance()->OnAddSession(lpPerSocketContext->Socket);
	// ��ʼ׼������...
	DWORD dwFlags = 0;
	DWORD dwRealRecv = 0;
	if (WSARecv(lpPerSocketContext->Socket, &(lpPerSocketContext->pIOContent->WsaBuf), 1,
		&dwRealRecv, &dwFlags, &(lpPerSocketContext->pIOContent->Overlapped), NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSA_IO_PENDING)
		{
			std::cout << "func WSARecv recving..." << std::endl;
		}
	}

	return 0;
}

bool CServer::CreateThreads()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int nProcessNUM = sysInfo.dwNumberOfProcessors;
	printf_s("start work thread num = %d\n", 2 * nProcessNUM);
	// ����worker�̳߳�
	m_pWorkThread = new HANDLE[2 * nProcessNUM];
	for (int i = 0; i < 2 * nProcessNUM; ++i)
	{
		m_pWorkThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPrc, this, 0, NULL);
		if (m_pWorkThread == NULL)
		{
			printf("�̳߳ش�������!\n");
			return false;
		}
	}
	return true;
}


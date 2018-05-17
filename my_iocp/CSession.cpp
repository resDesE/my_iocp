#include "stdafx.h"
#include "CSession.h"
#include "SvrDef.h"

CSession::CSession()
{
	m_fdSocket = INVALID_SOCKET;
	m_nSessionIndex = 0;
	m_nDstAddressPort = -1;
	m_nCurrentConnStatus = SESSION_CONNECT_CLOSE;
}

CSession::CSession(SOCKET sck)
{
	m_fdSocket = sck;
	m_nSessionIndex = 0;
	m_nDstAddressPort = -1;
	m_nCurrentConnStatus = SESSION_CONNECT_CLOSE;
}

CSession::~CSession()
{
	if (INVALID_SOCKET != m_fdSocket)
	{
		// break

	}
}

CSession& CSession::operator=(const CSession& src)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

CSession::CSession(const CSession& src)
{
	m_fdSocket = src.m_fdSocket;
	m_nSessionIndex = src.m_nSessionIndex;
	m_nDstAddressPort = src.m_nDstAddressPort;
	m_nCurrentConnStatus = src.m_nCurrentConnStatus;
	m_strDstAddressIPV4 = src.m_strDstAddressIPV4;
}

void CSession::OnSetSessionSock(SOCKET sock)
{
	m_fdSocket = sock;
}

void CSession::OnSetSessionAddressIPV4(const char* pIP, int nPort)
{
	m_strDstAddressIPV4 = pIP;
	m_nDstAddressPort = nPort;
}

void CSession::OnSetSessionStatus(int nStatus)
{
	m_nCurrentConnStatus = nStatus;
}

int CSession::OnReqest(PER_IO_CONTEXT* pIoContent)
{
	if (nullptr == pIoContent)
	{
		return -1;
	}

	return 0;
}

SOCKET CSession::OnGetSessionSocket()
{
	return m_fdSocket;
}

//session def
#pragma once

#include <string>
#include "../common/baseDef.h"

class CSession
{
public:
	CSession();
	CSession(SOCKET sck);
	~CSession();
	CSession& operator=(const CSession& src);
	CSession(const CSession& src);
public:
	void OnSetSessionSock(SOCKET sock);
	void OnSetSessionAddressIPV4(const char* pIP, int nPort);
	void OnSetSessionStatus(int nStatus);
public:
	int OnReqest(PER_IO_CONTEXT* pIoContent);
public:
	SOCKET OnGetSessionSocket();

private:
	SOCKET m_fdSocket;	// 会话socket
	int m_nSessionIndex;	// 会话index
	std::string m_strDstAddressIPV4;	// 会话目标ipv4地址
	int m_nDstAddressPort;	// 会话目标端口
	int m_nCurrentConnStatus;	// 会话当前连接状态
};
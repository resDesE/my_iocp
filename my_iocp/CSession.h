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
	SOCKET m_fdSocket;	// �Ựsocket
	int m_nSessionIndex;	// �Ựindex
	std::string m_strDstAddressIPV4;	// �ỰĿ��ipv4��ַ
	int m_nDstAddressPort;	// �ỰĿ��˿�
	int m_nCurrentConnStatus;	// �Ự��ǰ����״̬
};
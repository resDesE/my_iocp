#pragma once

#include <string>

// session conn status begin
#define SESSION_CONNECT_OK		0
#define SESSION_CONNECT_WAIT	1
#define SESSION_CONNECT_BREAK	2
#define SESSION_CONNECT_TRY		4
#define SESSION_CONNECT_CLOSE	5


// session conn status end


typedef struct _tagSESSIONHOSTINFO
{
	long long llSessionBuildTime;	// session����ʱ��
	std::string strHostIpv4Addr;	// session ipv4��ַ
	int nRemotePort;	// session host Զ�˶˿�
}SESSIONHOSTINFO, *pSESSIONHOSTINFO;

#pragma once

#include "CSession.h"
#include <map>
#include "singaleT.h"

typedef std::map<SOCKET, CSession*> MAPSESSIONINFO;

class CSessionMgr:public CSingaleT<CSessionMgr>
{
public:
	CSessionMgr();

	~CSessionMgr();
public:
	int OnAddSession(SOCKET sockSession);	// ����һ��session

	int OnDelSession(SOCKET sock);	// ɾ����Ӧsession

	CSession* OnGetSessionBySock(SOCKET sockSession);	// ��ѯ������session
private:
	MAPSESSIONINFO m_mapSessionInfos;
};



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
	int OnAddSession(SOCKET sockSession);	// 增加一个session

	int OnDelSession(SOCKET sock);	// 删除对应session

	CSession* OnGetSessionBySock(SOCKET sockSession);	// 查询并返回session
private:
	MAPSESSIONINFO m_mapSessionInfos;
};


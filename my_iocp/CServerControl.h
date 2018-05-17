#pragma once
#include "stdafx.h"
#include "../common/baseDef.h"
#include <list>
#include "Request.h"

class CServerControl
{
public:
	CServerControl();
	~CServerControl();
	int OnAddRequest(CRequest* pReq);
private:
	int OnInit();
	CRequest* GetReq();
private:
	std::list<CRequest*> m_listRequest;
};

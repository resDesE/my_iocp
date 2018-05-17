// 此文件进行相关功能的逻辑处理
// create by blackE, 20170603

#include "stdafx.h"
#include "CServerControl.h"
#include <iostream>
#include "CServer.h"


#include <threadpoolapiset.h>

//extern std::map <SOCKET, pPER_SOCKET_CONTEXT> _CurrentCon;

CServerControl::CServerControl()
{
}

CServerControl::~CServerControl()
{
	// to what
}


void CALLBACK WorkCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Parameter, PTP_WORK  Work)
{

}

int CServerControl::OnInit()
{
	// 初始化线程池
	PTP_POOL ptpPool = CreateThreadpool(NULL);
	if (NULL == ptpPool)
	{
		return -1;
	}

	SetThreadpoolThreadMinimum(ptpPool, 2);
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	SetThreadpoolThreadMaximum(ptpPool, sysInfo.dwNumberOfProcessors * 5);

	TP_CALLBACK_ENVIRON tpCallEnv;
	InitializeThreadpoolEnvironment(&tpCallEnv);

	SetThreadpoolCallbackPool(&tpCallEnv, ptpPool);

	PTP_WORK_CALLBACK ptpWork = NULL;
	CreateThreadpoolWork(ptpWork, NULL, &tpCallEnv);



	return 0;
}

//file
#pragma once
#include "../singaleT.h"




class CThreadPool :public CSingaleT<CThreadPool>
{
public:
	CThreadPool();
	~CThreadPool();
public:
	int OnInit(int nThreadNum = 0);	// 初始化，输入线程数，0：根据机器自动生成CPU核数*2
	void OnDestroy();
public:
	int OnAddTask()
};
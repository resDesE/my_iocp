//file
#pragma once
#include "../singaleT.h"




class CThreadPool :public CSingaleT<CThreadPool>
{
public:
	CThreadPool();
	~CThreadPool();
public:
	int OnInit(int nThreadNum = 0);	// ��ʼ���������߳�����0�����ݻ����Զ�����CPU����*2
	void OnDestroy();
public:
	int OnAddTask()
};
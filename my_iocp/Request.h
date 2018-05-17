#pragma once


#include "../common/baseDef.h"


class CRequest
{
public:
	CRequest();
	CRequest(PER_IO_CONTEXT* pIoContent);
	virtual ~CRequest();
public:
	virtual void Run();
private:
	PER_IO_CONTEXT* m_pIoContent;	// IO±¨ÎÄ
};
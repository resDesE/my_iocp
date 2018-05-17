#pragma once

#include "../../common/baseDef.h"

class CTask
{
public:
	CTask();
	virtual ~CTask();
public:
	virtual int Run();
private:

};
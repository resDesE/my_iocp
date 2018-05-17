//
#pragma once


template<typename T>
class CSingaleT
{
public:
	CSingaleT() {}

	~CSingaleT() {}
	static T* Instance()
	{
		static T _instance;
		return &_instance;
	}
};
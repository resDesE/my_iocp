// 对临界区/互斥区进行初始化--InitializeCriticalSection，并封装出AutoLock
// 临界区/互斥区必须先初始化
// 进入临界区--EnterCriticalSection
// 离开临界区--LeaveCriticalSection
// 锁用完后必须释放锁，否则死锁
// create by blackE, 20170604

#pragma once


class cMutex {
	CRITICAL_SECTION _cs;
public:
	cMutex() { ::InitializeCriticalSection(&_cs); }
	~cMutex() { ::DeleteCriticalSection(&_cs); }

	__forceinline CRITICAL_SECTION* operator&() { return &_cs; }
	__forceinline operator CRITICAL_SECTION&() { return _cs; }

	cMutex(const cMutex&) = delete;
	cMutex& operator=(const cMutex&) = delete;
};

class cAutoLock {
	CRITICAL_SECTION& _refLock; // 存引用节省判空操作(比指针)
public:
	cAutoLock(CRITICAL_SECTION& mutex) : _refLock(mutex) // 对象构建，进入临界区
	{
		InitializeCriticalSection(&_refLock);
		EnterCriticalSection(&_refLock);
	}
	// 对象析构，退出临界区
	~cAutoLock()
	{ 
		// 释放临界区但不删除临界区
		LeaveCriticalSection(&_refLock);
//		DeleteCriticalSection(&_refLock);	// 在引用状态下勿加入此行，这个请谨慎使用....
	}
};
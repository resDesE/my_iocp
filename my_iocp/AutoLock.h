// ���ٽ���/���������г�ʼ��--InitializeCriticalSection������װ��AutoLock
// �ٽ���/�����������ȳ�ʼ��
// �����ٽ���--EnterCriticalSection
// �뿪�ٽ���--LeaveCriticalSection
// �����������ͷ�������������
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
	CRITICAL_SECTION& _refLock; // �����ý�ʡ�пղ���(��ָ��)
public:
	cAutoLock(CRITICAL_SECTION& mutex) : _refLock(mutex) // ���󹹽��������ٽ���
	{
		InitializeCriticalSection(&_refLock);
		EnterCriticalSection(&_refLock);
	}
	// �����������˳��ٽ���
	~cAutoLock()
	{ 
		// �ͷ��ٽ�������ɾ���ٽ���
		LeaveCriticalSection(&_refLock);
//		DeleteCriticalSection(&_refLock);	// ������״̬���������У���������ʹ��....
	}
};
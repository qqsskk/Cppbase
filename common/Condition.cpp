#include "stdafx.h"
#include "Condition.h"
#include <condition_variable>

/*
线程创建			pthread_create			CreateThread
退出				pthread_exit			ThreadExit
等待				pthread_join			WaitForSingleObject
互斥锁创建		pthread_mutex_init		CreateMutex
销毁				pthread_mutex_destroy	CloseHandle
加锁				pthread_mutex_lock		WaitForSingleObject
解锁				pthread_mutex_unlock	ReleaseMutex
条件创建			pthread_cond_init		CreateEvent
销毁				pthread_cond_destroy	CloseHandle
触发				pthread_cond_signal		SetEvent
广播				pthread_cond_broadcast	SetEvent / ResetEvent
等待				pthread_cond_wait / pthread_cond_timedwait	SingleObjectAndWait
*/
namespace FacileLib
{
	Condition::Condition(CLock* pLock)
		:m_cond(pLock)
	{
#ifdef WIN32
		m_cond = ::CreateEvent(NULL, TRUE, FALSE, NULL);
#else
		pthread_cond_init(&m_cond, NULL);
#endif // WIN32
	}


	Condition::~Condition()
	{
#ifdef WIN32
		::CloseHandle(m_cond);
#else
		pthread_cond_destroy(&m_cond, NULL);
#endif // WIN32
		
	}
#pragma warning (disable: 4244)

	bool Condition::waitTime(uint64_t nWaitTime)
	{
#ifdef WIN32
		if (WAIT_TIMEOUT == SignalObjectAndWait(m_cond, m_pLock->getLock(), nWaitTime, FALSE))
		{
			return false;
		}
		return true;
#else
		uint64_t nTime = nWaitTime * 1000000;
		struct timespec sTime;
		uint64_t nSec = nTime / (1000000000);
		uint64_t nNsec = nTime % (1000000000);
		sTime.tv_sec = time(NULL) + (uint32_t)nSec;
		sTime.tv_nsec = (uint32_t)nNsec;
		if (ETIMEDOUT == pthread_cond_timedwait(&m_cond, &m_pLock->getMutex(), &sTime))
		{
			return false;
		}
		return true;
#endif // WIN32
		
	}
	void Condition::notify()
	{
#ifdef WIN32
		SetEvent(m_cond);
#else
		pthread_cond_signal(&m_cond);
#endif // WIN32	
	}
	void Condition::notifyAll()
	{
#ifdef WIN32
		ResetEvent(m_cond);
#else
		pthread_cond_broadcast(&m_cond);
#endif // WIN32
	}
}

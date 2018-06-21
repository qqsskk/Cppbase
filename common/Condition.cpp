#include "stdafx.h"
#include "Condition.h"
#include <condition_variable>

/*
�̴߳���			pthread_create			CreateThread
�˳�				pthread_exit			ThreadExit
�ȴ�				pthread_join			WaitForSingleObject
����������		pthread_mutex_init		CreateMutex
����				pthread_mutex_destroy	CloseHandle
����				pthread_mutex_lock		WaitForSingleObject
����				pthread_mutex_unlock	ReleaseMutex
��������			pthread_cond_init		CreateEvent
����				pthread_cond_destroy	CloseHandle
����				pthread_cond_signal		SetEvent
�㲥				pthread_cond_broadcast	SetEvent / ResetEvent
�ȴ�				pthread_cond_wait / pthread_cond_timedwait	SingleObjectAndWait
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

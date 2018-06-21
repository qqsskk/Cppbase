#pragma once
#include "ostype.h"

/*
C++11 #include <lock>
C++11�Դ�mutex,���������汾�ϵͿ�ʹ������ķ���
*/
namespace FacileLib{

	class CLock
	{
	public:
		CLock();
		virtual ~CLock();
		void lock();
		void unlock();
#ifdef _WIN32
		HANDLE getLock() { return m_lock; }
#else		
		virtual bool try_lock();
		pthread_mutex_t& getLock() { return m_lock; }
#endif
	private:
#ifdef _WIN32	
		HANDLE m_lock;
#else
		pthread_mutex_t m_lock;
#endif
	};

#ifndef _WIN32
	class CRWLock
	{
	public:
		CRWLock();
		virtual ~CRWLock();
		void rlock();
		void wlock();
		void unlock();
		bool try_rlock();
		bool try_wlock();
	private:
		pthread_rwlock_t m_lock;
	};

	class CAutoRWLock
	{
	public:
		CAutoRWLock(CRWLock* pLock, bool bRLock = true);
		virtual ~CAutoRWLock();
	private:
		CRWLock* m_pLock;
	};

#endif

	class CAutoLock
	{
	public:
		CAutoLock(CLock* pLock);
		virtual ~CAutoLock();
	private:
		CLock* m_pLock;
	};
}
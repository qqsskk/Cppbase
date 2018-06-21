#pragma once
#include "ostype.h"
#include "Lock.h"
/*
C++11 #include <condition_variable>
C++11�Դ�thread,���������汾�ϵͿ�ʹ������ķ���
*/
namespace FacileLib{

	class Condition
	{
	public:
		Condition(CLock* pLock);
		~Condition();
		void wait();
		//��λΪ����
		bool waitTime(uint64_t nWaitTime);
		void notify();
		void notifyAll();
	private:
		CLock* m_pLock;
#ifdef WIN32
		HANDLE m_cond;
#else
		pthread_cond_t m_cond;
#endif // WIN32
	};

}



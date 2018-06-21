#pragma once
#include "ostype.h"
#include "Lock.h"
/*
C++11 #include <condition_variable>
C++11自带thread,若编译器版本较低可使用下面的方法
*/
namespace FacileLib{

	class Condition
	{
	public:
		Condition(CLock* pLock);
		~Condition();
		void wait();
		//单位为毫秒
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



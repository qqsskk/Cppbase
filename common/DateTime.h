#pragma once
#include "ostype.h"
#ifndef WIN32
typedef struct _SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} 	SYSTEMTIME;
#endif

namespace FacileLib{

	class DateTime{
	public:
		DateTime();
		DateTime(SYSTEMTIME& st);
		~DateTime();

		static bool IsLeapYear(unsigned int p_year);
		bool ValidateDate();
		bool Validate();

		void IncYear(int years);
		void IncMonth(int months);
		void IncDay(int days);
		void IncHour(int hours);
		void IncMinute(int minutes);
		void IncSecond(int seconds);
		void IncWeek(int weeks);

		//��yyyy - mm - dd hh : nn : ss�ĸ�ʽ����һ�����ڵ��ַ�����ʽ
		std::string FormatStr();
		std::wstring FormatstrW();

		//��yyyy-mm-dd�ĸ�ʽ����һ�����ڵ��ַ�����ʽ
		std::string FormatDate(const SYSTEMTIME &st);
		std::wstring FormatDateW(const SYSTEMTIME &st);

		//��hh:nn:ss�ĸ�ʽ����һ�����ڵ��ַ�����ʽ
		std::string FormatTime(const SYSTEMTIME &st);
		std::wstring FormatTimeW(const SYSTEMTIME &st);
	public:
		//��ת��Ϊ��ǰʱ��
		static SYSTEMTIME now();
		//���ָ�������ʱ��
		static SYSTEMTIME uac();
		//��ȡʱ��
		static SYSTEMTIME get();
		static void t2tm(long long time, SYSTEMTIME& st);
		static void tm2t(long long& time, const SYSTEMTIME& st);
	private:
		SYSTEMTIME dt_;
	};

	inline int YearsBetween(DateTime &p_now, DateTime &p_then);
	inline int MonthsBetween(DateTime &p_now, DateTime &p_then);
	inline int DaysBetween(DateTime &p_now, DateTime &p_then);
	inline int HoursBetween(DateTime &p_now, DateTime &p_then);
	inline int MinutesBetween(DateTime &p_now, DateTime &p_then);
	inline long long SecondsBetween(DateTime &p_now, DateTime &p_then);
	inline int WeeksBetween(DateTime &p_now, DateTime &p_then);


};




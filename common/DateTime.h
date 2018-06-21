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

		//以yyyy - mm - dd hh : nn : ss的格式返回一个日期的字符串格式
		std::string FormatStr();
		std::wstring FormatstrW();

		//以yyyy-mm-dd的格式返回一个日期的字符串格式
		std::string FormatDate(const SYSTEMTIME &st);
		std::wstring FormatDateW(const SYSTEMTIME &st);

		//以hh:nn:ss的格式返回一个日期的字符串格式
		std::string FormatTime(const SYSTEMTIME &st);
		std::wstring FormatTimeW(const SYSTEMTIME &st);
	public:
		//会转换为当前时区
		static SYSTEMTIME now();
		//格林格林威治时间
		static SYSTEMTIME uac();
		//获取时间
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




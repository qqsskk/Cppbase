#include "stdafx.h"
#include "DateTime.h"
#include <time.h>
#ifndef WIN32
	#include <sys/time.h>
#endif // WIN32


namespace FacileLib
{
	DateTime::DateTime()
	{
	}


	DateTime::~DateTime()
	{
	}

	bool DateTime::IsLeapYear(unsigned int p_year)
	{
		return ((p_year % 400 == 0) || (p_year % 4 == 0)) && (p_year % 100 != 0);
	}

	bool DateTime::ValidateDate()
	{
		if (dt_.wMonth > 12 || dt_.wMonth == 0
			|| dt_.wDay > 31 || dt_.wDay == 0
			|| (dt_.wMonth == 2 && IsLeapYear(dt_.wYear) && dt_.wDay > 29)
			|| (dt_.wMonth == 2 && (!IsLeapYear(dt_.wYear)) && dt_.wDay > 28)
			|| ((dt_.wMonth == 4 || dt_.wMonth == 6 || dt_.wMonth == 9 || dt_.wMonth == 11) && dt_.wDay > 30)
			)
			return false;
		return true;
	}

	bool DateTime::Validate()
	{
		if (!ValidateDate())
			return false;
		return (dt_.wHour >= 0 && dt_.wHour < 24 && dt_.wMinute >= 0 && dt_.wMinute < 60 && dt_.wSecond >= 0 && dt_.wSecond < 60 && dt_.wMilliseconds >= 0 && dt_.wMilliseconds < 1000);
	}

	void DateTime::IncYear(int years)
	{
		dt_.wYear += years;
	}

	void DateTime::IncMonth(int months)
	{
		int y = months / 12;
		int m = months % 12;
		IncYear(y);
		while (m > 0)
		{
			--m;
			++(dt_.wMonth);
			if (dt_.wMonth > 12)
			{
				++(dt_.wYear);
				dt_.wMonth = 1;
			}
		}
		if (dt_.wMonth == 2)
		{
			if (dt_.wDay > 29 && IsLeapYear(dt_.wYear))
				dt_.wDay = 29;
			if (dt_.wDay > 28 && !IsLeapYear(dt_.wYear))
				dt_.wDay = 28;
		}
		else if (dt_.wMonth == 4 || dt_.wMonth == 6 || dt_.wMonth == 9 || dt_.wMonth == 11)
		{
			if (dt_.wDay > 30)
				dt_.wDay = 30;
		}
	}

	void DateTime::IncDay(int days)
	{
		time_t t = 0;
		tm2t(t, dt_);
		t += (days * 24 * 60 * 60);
		SYSTEMTIME dt;
		t2tm(t, dt);
		dt.wMilliseconds = dt_.wMilliseconds;
		dt_ = dt;
	}

	void DateTime::IncHour(int hours)
	{
		time_t t = 0;
		tm2t(t, dt_);
		t += (hours * 60 * 60);
		SYSTEMTIME dt;
		t2tm(t, dt);
		dt.wMilliseconds = dt_.wMilliseconds;
		dt_ = dt;
	}

	void DateTime::IncMinute(int minutes)
	{
		time_t t = 0;
		tm2t(t, dt_);
		//每天的时间是固定的
		t += (minutes * 60);
		SYSTEMTIME dt;
		t2tm(t, dt);
		dt.wMilliseconds = dt_.wMilliseconds;
		dt_ = dt;
	}

	void DateTime::IncSecond(int seconds)
	{
		time_t t = 0;
		tm2t(t, dt_);
		//每天的时间是固定的
		t += seconds;
		SYSTEMTIME dt;
		t2tm(t, dt);
		dt.wMilliseconds = dt_.wMilliseconds;
		dt_ = dt;
	}

	void DateTime::IncWeek(int weeks)
	{
		IncDay(7 * weeks);
	}

	std::string DateTime::FormatStr()
	{
		char cst[30] = { 0 };
		sprintf_s(cst, "%4d-%02d-%02d %02d:%02d:%02d:%03d", dt_.wYear, dt_.wMonth, dt_.wDay, dt_.wHour, dt_.wMinute, dt_.wSecond, dt_.wMilliseconds);
		return std::string(cst);
	}

	std::wstring DateTime::FormatstrW()
	{
		wchar_t cst[30] = { 0 };
		swprintf_s(cst, L"%4d-%02d-%02d %02d:%02d:%02d:%03d", dt_.wYear, dt_.wMonth, dt_.wDay, dt_.wHour, dt_.wMinute, dt_.wSecond, dt_.wMilliseconds);
		return std::wstring(cst);
	}

	std::string DateTime::FormatDate(const SYSTEMTIME &st)
	{
		char cst[30] = { 0 };
		sprintf_s(cst, "%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
		return std::string(cst);
	}

	std::wstring DateTime::FormatDateW(const SYSTEMTIME &st)
	{
		wchar_t cst[30] = { 0 };
		swprintf_s(cst, L"%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
		return std::wstring(cst);
	}

	std::string DateTime::FormatTime(const SYSTEMTIME &st)
	{
		char cst[30] = { 0 };
		sprintf_s(cst, "%02d:%02d:%02d:%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		return std::string(cst);
	}

	std::wstring DateTime::FormatTimeW(const SYSTEMTIME &st)
	{
		wchar_t cst[30] = { 0 };
		swprintf_s(cst, L"%02d:%02d:%02d:%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		return std::wstring(cst);
	}

	SYSTEMTIME DateTime::now()
	{
		SYSTEMTIME st;
	#ifdef WIN32
		::GetLocalTime(&st);
	#else
		struct timeval tv;
		struct timezone tz;
		gettimeofday(&tv,&tz);
		int64_t tsec = time.tv_sec - tz.tz_minuteswest * 60;
		t2tm(tsec,st);
		st.wMilliseconds = tv.tv_usec/1000;		
	#endif // WIN32
		return st;
	}

	SYSTEMTIME DateTime::uac()
	{
		SYSTEMTIME st;
#ifdef WIN32
		::GetSystemTime(&st);
#else
		struct timeval tv;
		struct timezone tz;
		gettimeofday(&tv, &tz);
		t2tm(tsec, st);
		st.wMilliseconds = tv.tv_usec/1000;
#endif // WIN32
		return st;
	}

	void DateTime::t2tm(long long time, SYSTEMTIME& st)
	{
		tm temptm;
		localtime_s(&temptm, &time);
		st.wYear = 1900 + temptm.tm_year;
		st.wMonth = temptm.tm_mon + 1;
		st.wDayOfWeek = temptm.tm_wday;
		st.wDay = temptm.tm_mday;
		st.wHour = temptm.tm_hour;
		st.wMinute = temptm.tm_min;
		st.wSecond = temptm.tm_sec;
		st.wMilliseconds = 0;
	}

	void DateTime::tm2t(long long& time, const SYSTEMTIME& st)
	{
		tm temptm = { st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };
		time = mktime(&temptm);
	}

	int YearsBetween(DateTime &p_now, DateTime &p_then)
	{
		return p_then.get().wYear - p_now.get().wYear;
	}

	int MonthsBetween(DateTime &p_now, DateTime &p_then)
	{
		if (!p_now.Validate() || !p_then.Validate())
			return 0;
		return YearsBetween(p_now, p_then) * 12 + (p_then.get().wMonth - p_now.get().wMonth);
	}

	int DaysBetween(DateTime &p_now, DateTime &p_then)
	{
		if (!p_now.Validate() || !p_then.Validate())
			return 0;
		SYSTEMTIME dtNow, dtThen;
		int x;
		if (p_now.get().wYear < p_then.get().wYear
			|| (p_now.get().wYear == p_then.get().wYear && p_now.get().wMonth < p_then.get().wMonth)
			|| (p_now.get().wYear == p_then.get().wYear && p_now.get().wMonth == p_then.get().wMonth && p_now.get().wDay < p_then.get().wDay)
			)
		{
			dtNow = p_now.get();
			dtThen = p_then.get();
			x = 1;
		}
		else
		{
			dtNow = p_then.get();
			dtThen = p_now.get();
			x = -1;
		}
		int ret = 0;
		while (true)
		{
			if (dtNow.wYear == dtThen.wYear && dtNow.wMonth == dtThen.wMonth && dtNow.wDay == dtThen.wDay)
				break;
			++ret;
			++(dtNow.wDay);

			if (dtNow.wMonth == 2)
			{
				if (dtNow.wDay > 28 && !DateTime::IsLeapYear(dtNow.wYear))
				{
					dtNow.wMonth = 3;
					dtNow.wDay = 1;
				}
				else if (dtNow.wDay > 29)
				{
					dtNow.wMonth = 3;
					dtNow.wDay = 1;
				}
			}
			else if (dtNow.wDay > 30 && (dtNow.wMonth == 4 || dtNow.wMonth == 6 || dtNow.wMonth == 9 || dtNow.wMonth == 11))
			{
				++(dtNow.wMonth);
				dtNow.wDay = 1;
			}
			else if (dtNow.wDay > 31 && (dtNow.wMonth == 1 || dtNow.wMonth == 3 || dtNow.wMonth == 5 || dtNow.wMonth == 7 || dtNow.wMonth == 8 || dtNow.wMonth == 10 || dtNow.wMonth == 12))
			{
				++(dtNow.wMonth);
				dtNow.wDay = 1;
				if (dtNow.wMonth > 12)
				{
					++(dtNow.wYear);
					dtNow.wMonth = 1;
				}
			}
		}

		return ret*x;
	}

	int HoursBetween(DateTime &p_now, DateTime &p_then)
	{
		if (!p_now.Validate() || !p_then.Validate())
			return 0;
		return DaysBetween(p_now, p_then) * 24 + (p_then.get().wHour - p_now.get().wHour);
	}

	int MinutesBetween(DateTime &p_now, DateTime &p_then)
	{
		if (!p_now.Validate() || !p_then.Validate())
			return 0;
		return HoursBetween(p_now, p_then) * 60 + (p_then.get().wMinute - p_now.get().wMinute);
	}

	long long SecondsBetween(DateTime &p_now, DateTime &p_then)
	{
		if (!p_now.Validate() || !p_then.Validate())
			return 0;
		return HoursBetween(p_now, p_then) * 60 + (p_then.get().wMinute - p_now.get().wMinute);
	}

	int WeeksBetween(DateTime &p_now, DateTime &p_then)
	{
		return DaysBetween(p_now, p_then) / 7;
	}

}
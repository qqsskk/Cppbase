#include "stdafx.h"
#include "Util.h"
using namespace std;

namespace FacileLib{

	CRefObject::CRefObject()
	{
		m_lock = NULL;
		m_refCount = 1;
	}

	CRefObject::~CRefObject()
	{

	}

	void CRefObject::AddRef()
	{
		if (m_lock)
		{
			m_lock->lock();
			m_refCount++;
			m_lock->unlock();
		}
		else
		{
			m_refCount++;
		}
	}

	void CRefObject::ReleaseRef()
	{
		if (m_lock)
		{
			m_lock->lock();
			m_refCount--;
			if (m_refCount == 0)
			{
				delete this;
				return;
			}
			m_lock->unlock();
		}
		else
		{
			m_refCount--;
			if (m_refCount == 0)
				delete this;
		}
	}

	std::string& ReplaceString(std::string &s, const std::string &OldPattern, const std::string &NewPattern)
	{
		if (OldPattern == NewPattern)
			return s;
		string::size_type i;
		while (true)
		{
			i = s.find(OldPattern);
			if (i == string::npos)
				break;
			else
				s = s.replace(i, OldPattern.length(), NewPattern);
		}
		return s;
	}

	std::wstring& ReplaceStringW(std::wstring &s, const std::wstring &OldPattern, const std::wstring &NewPattern)
	{
		if (OldPattern == NewPattern)
			return s;
		wstring::size_type i;
		while (true)
		{
			i = s.find(OldPattern);
			if (i == wstring::npos)
				break;
			else
				s = s.replace(i, OldPattern.length(), NewPattern);
		}
		return s;
	}

	
	void SplitString(const string &AString, const string &ASplitStr, vector<string> &AStrings)
	{
		const char *sdata = AString.c_str();
		const char *ssplit = ASplitStr.c_str();
		DWORD i = 0, j = 0, iSizeA = AString.length(), iSizeB = ASplitStr.length();
		AStrings.clear();
		while (i < iSizeA)
		{
			if (i + iSizeB > iSizeA)
			{
				AStrings.push_back(AString.substr(j));
				j = i;
				break;
			}
			if (memcmp(&(sdata[i]), ssplit, iSizeB) == 0)
			{
				//if (j < i)
				AStrings.push_back(AString.substr(j, i - j));
				j = i + iSizeB;
				i += iSizeB;
			}
			else
				++i;
		}
		if (j < i)
			AStrings.push_back(AString.substr(j));
		return;
	}

	void SplitString(const string &AString, const string &ASplitStr, string &ALeft, string &ARight)
	{
		vector<string> vs;
		SplitString(AString, ASplitStr, vs);
		ALeft = vs[0];
		ARight = "";
		if (vs.size() > 1)
		{
			for (size_t i = 1; i != vs.size(); ++i)
			{
				if (ARight.empty())
					ARight = vs[i];
				else
					ARight = ARight + ASplitStr + vs[i];
			}
		}
		else
			ARight = "";
		return;
	}

	void SplitStringW(const wstring &AString, const wstring &ASplitStr, vector<wstring> &dest)
	{
		wstring::size_type pos = wstring::npos;
		wstring::size_type offset = 0;
		dest.clear();
		while (1)
		{
			pos = AString.find(ASplitStr.c_str(), offset);
			if (wstring::npos == pos)
				break;
			dest.push_back(AString.substr(offset, pos - offset));
			offset = ASplitStr.length() + pos;

		}
		if (offset != AString.length())
			dest.push_back(AString.substr(offset));
	}

	void SplitStringW(const wstring &AString, const wstring &ASplitStr, wstring &ALeft, wstring &ARight)
	{
		vector<wstring> vs;
		SplitStringW(AString, ASplitStr, vs);
		ALeft = vs[0];
		if (vs.size() > 1)
		{
			for (size_t i = 1; i != vs.size(); ++i)
			{
				if (ARight.empty())
					ARight = vs[i];
				else
					ARight = ARight + ASplitStr + vs[i];
			}
		}
		else
			ARight = L"";
		return;
	}



	std::string ConcatString(std::vector<std::string> vecStr)
	{
		if (0 == vecStr.size())
			return "";
		string strRet;
		for (unsigned int i = 0; i < vecStr.size(); i++)
		{
			strRet += vecStr[i];
		}
		return strRet;
	}

	std::wstring ConcatStringW(std::vector<std::wstring> vecStr)
	{
		if (0 == vecStr.size())
			return L"";
		wstring strRet;
		for (unsigned int i = 0; i < vecStr.size(); i++)
		{
			strRet += vecStr[i];
		}
		return strRet;
	}

	std::string StringList2String(const vector<string> &AStringList, const string &AConnectStr)
	{
		string ret;
		for (vector<string>::const_iterator it = AStringList.begin(); it != AStringList.end(); ++it)
		{
			if (ret.empty())
				ret = *it;
			else
				ret = ret + AConnectStr + *it;
		}
		return ret;
	}

	std::string StringList2String(const list<string> &AStringList, const string &AConnectStr)
	{
		string ret;
		for (list<string>::const_iterator it = AStringList.begin(); it != AStringList.end(); ++it)
		{
			if (ret.empty())
				ret = *it;
			else
				ret = ret + AConnectStr + *it;
		}
		return ret;
	}

	wstring StringList2StringW(const vector<wstring> &AStringList, const wstring &AConnectStr)
	{
		wstring ret;
		for (vector<wstring>::const_iterator it = AStringList.begin(); it != AStringList.end(); ++it)
		{
			if (ret.empty())
				ret = *it;
			else
				ret = ret + AConnectStr + *it;
		}
		return ret;
	}

	wstring StringList2StringW(const list<wstring> &AStringList, const wstring &AConnectStr)
	{
		wstring ret;
		for (list<wstring>::const_iterator it = AStringList.begin(); it != AStringList.end(); ++it)
		{
			if (ret.empty())
				ret = *it;
			else
				ret = ret + AConnectStr + *it;
		}
		return ret;
	}

	std::string StrFormat(const char *fmt, ...)
	{
		std::string strResult = "";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数 
			size_t nLength = _vscprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<char> vBuffer(nLength, '\0');        //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
		}
		return strResult;
	}

	wstring StrFormatW(const wchar_t *fmt, ...)
	{
		std::wstring strResult = L"";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数
			size_t nLength = _vscwprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<wchar_t> vBuffer(nLength, L'\0');    //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnwprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
		}
		return strResult;
	}

	#define int2hex(a) ((a)<10?(a)+'0':(a)+'a'-10)
	#define hex2int(a) ((a)>='a'?(a)-'a'+10:(a)-'0')

	static char char2print(char a)
	{
		if ((a >= 32) && (a <= 126))return a;
		return '.';
	}

	static std::string bin2print(const std::string &in, int size)
	{
		const char *buf = in.c_str();
		std::string out("");
		std::string inp("");
		for (unsigned int i = 0; i < (unsigned)size; i++)
		{
			unsigned char tmp = i < in.length() ? buf[i] : ' ';
			inp += char2print(tmp);
			out += i < in.length() ? int2hex(tmp >> 4) : ' ';
			out += i < in.length() ? int2hex(tmp & 0x0f) : ' ';
			out += ' ';
			if ((i % 4) == 3) out += ' ';
		}
		out += inp + "\r\n";
		return out;
	}

	std::string bin2hex(const std::string &in, int size /*= 0*/)
	{
		const char *buf = in.c_str();
		std::string out("");
		int i = 0, j = 0;
		for (i; (unsigned)i < in.length(); i++)
		{
			char tmp = buf[i];
			if (!size)
			{
				out += int2hex((tmp >> 4) & 0x0f);
				out += int2hex(tmp & 0x0f);
			}
			else
			{
				out += bin2print(in.substr(i, size), size);
				i += size - 1;
			}
		}

		return out;
	}

	std::string hex2bin(const std::string &in)
	{
		const char *buf = in.c_str();
		std::string out("");
		int i = 0;
		for (i; (unsigned)i < in.length(); i += 2)
		{
			if (((buf[i] >= '0' && buf[i] <= '9') || (buf[i] >= 'a' && buf[i] <= 'f'))
				&& ((buf[i + 1] >= '0' && buf[i + 1] <= '9') || (buf[i + 1] >= 'a' && buf[i + 1] <= 'f'))) {
				char tmp = hex2int(buf[i]);
				char tmp1 = hex2int(buf[i + 1]);
				tmp = (tmp << 4) + tmp1;
				out += tmp;
			}
		}
		return out;
	}

	int itots_s(int val, TCHAR *buffer, size_t bufLen, int radix)
	{
#ifdef UNICODE
		return _itow_s(val, buffer, bufLen, radix);
#else
		return _itoa_s(val, buffer, bufLen, radix);
#endif
	}

	int uitots_s(unsigned int val, TCHAR *buffer, size_t bufLen, int radix)
	{
#ifdef UNICODE
		return _ultow_s((unsigned long)val, buffer, bufLen, radix);
#else
		return _ultoa_s((unsigned long)val, buffer, bufLen, radix);
#endif
	}

	int i64tots_s(INT64 val, TCHAR *buffer, size_t bufLen, int radix)
	{
#ifdef UNICODE
		return _i64tow_s(val, buffer, bufLen, radix);
#else
		return _i64toa_s(val, buffer, bufLen, radix);
#endif
	}

	int ui64tots_s(UINT64 val, TCHAR *buffer, size_t bufLen, int radix)
	{
#ifdef UNICODE
		return _ui64tow_s(val, buffer, bufLen, radix);
#else
		return _ui64toa_s((unsigned long)val, buffer, bufLen, radix);
#endif
	}

	int tstring_base_to_int(const TCHAR *nptr, TCHAR **endptr, int base)
	{
#ifdef UNICODE
		return (int)wcstol(nptr, endptr, base);
#else
		return (int)strtol(nptr, endptr, base);
#endif
	}

	unsigned int tstring_base_to_uint(const TCHAR *nptr, TCHAR **endptr, int base)
	{
#ifdef UNICODE
		return (unsigned int)wcstoul(nptr, endptr, base);
#else
		return (unsigned int)strtoul(nptr, endptr, base);
#endif
	}

	int64_t tstring_base_to_int64(const TCHAR *nptr, TCHAR **endptr, int base)
	{
#ifdef UNICODE
		return (int64_t)_wcstoi64(nptr, endptr, base);
#else
		return (int64_t)_strtoi64(nptr, endptr, base);
#endif

	}

	uint64_t tstring_base_to_uint64(const TCHAR *nptr, TCHAR **endptr, int base)
	{
#ifdef UNICODE
		return (uint64_t)_wcstoui64(nptr, endptr, base);
#else
		return (uint64_t)_strtoui64(nptr, endptr, base);
#endif
	}

	double tstof(TCHAR *lpFloat)
	{
#ifdef UNICODE
		return _wtof(lpFloat);
#else
		return atof(lpFloat);
#endif
	}

	int tstoi(TCHAR *lpInt)
	{
#ifdef UNICODE
		return _wtoi(lpInt);
#else
		return atoi(lpInt);
#endif
	}

	unsigned int tstoui(TCHAR *lpInt)
	{
		return (unsigned int)tstring_base_to_uint(lpInt, NULL, 10);
	}

	int64_t tstoi64(TCHAR *lpInt)
	{
#ifdef UNICODE
		return _wtoi64(lpInt);
#else
		return _atoi64(lpInt);
#endif
	}

	uint64_t tstoui64(TCHAR *lpInt)
	{
		return (UINT64)tstring_base_to_uint64(lpInt, NULL, 10);
	}

}

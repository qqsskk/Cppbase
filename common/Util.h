#pragma once
#include "ostype.h"
#include "Lock.h"

#define SafeDelete(p)   if(p) { delete (p); (p) = NULL;}  
#define SafeDelArry(p)  if(p) { delete []p; (p) = NULL;}  
#define SafeFree(p)   if(p) { free (p); (p) = NULL;}  
#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))
#define SafeRelease(var) if(var) {var->Release(); var = NULL;}


namespace FacileLib{

	class CRefObject
	{
	public:
		CRefObject();
		virtual ~CRefObject();

		void SetLock(CLock* lock) { m_lock = lock; }
		void AddRef();
		void ReleaseRef();
	private:
		int		m_refCount;
		CLock*	m_lock;
	};

	void SplitString(const std::string &AString, const std::string &ASplitStr, std::vector<std::string> &AStrings);
	void SplitStringW(const std::wstring &AString, const std::wstring &ASplitStr, std::vector<std::wstring> &AStrings);
	void SplitString(const std::string &AString, const std::string &ASplitStr, std::string &ALeft, std::string &ARight);
	void SplitStringW(const std::wstring &AString, const std::wstring &ASplitStr, std::wstring &ALeft, std::wstring &ARight);

	std::string StringList2String(const std::vector<std::string> &AStringList, const std::string &AConnectStr);
	std::wstring StringList2StringW(const std::vector<std::wstring> &AStringList, const std::wstring &AConnectStr);
	std::string StringList2String(const std::list<std::string> &AStringList, const std::string &AConnectStr);
	std::wstring StringList2StringW(const std::list<std::wstring> &AStringList, const std::wstring &AConnectStr);

	std::string ConcatString(std::vector<std::string> vecStr);
	std::wstring ConcatStringW(std::vector<std::wstring> vecStr);
	std::string StrFormat(const char *fmt, ...);
	std::wstring StrFormatW(const wchar_t *fmt, ...);

	std::string bin2hex(const std::string &in, int size = 0);
	std::string hex2bin(const std::string &in);

	int  itots_s(int val, TCHAR *buffer, size_t bufLen, int radix);
	int  uitots_s(unsigned int val, TCHAR *buffer, size_t bufLen, int radix);
	int  i64tots_s(INT64 val, TCHAR *buffer, size_t bufLen, int radix);
	int  ui64tots_s(UINT64 val, TCHAR *buffer, size_t bufLen, int radix);

	int	tstring_base_to_int(const TCHAR *nptr, TCHAR **endptr, int base);
	unsigned int tstring_base_to_uint(const TCHAR *nptr, TCHAR **endptr, int base);
	int64_t tstring_base_to_int64(const TCHAR *nptr, TCHAR **endptr, int base);
	uint64_t tstring_base_to_uint64(const TCHAR *nptr, TCHAR **endptr, int base);

	double            tstof(TCHAR *lpFloat);
	int               tstoi(TCHAR *lpInt);
	unsigned int	  tstoui(TCHAR *lpInt);
	int64_t           tstoi64(TCHAR *lpInt);
	uint64_t          tstoui64(TCHAR *lpInt);

}



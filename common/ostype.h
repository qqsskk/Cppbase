#ifndef __OS_TYPE_H__
#define __OS_TYPE_H__

#ifdef _WIN32
//#include <WinSock2.h>
#include <Windows.h>
#include <direct.h>
#else
#ifdef __APPLE__
#include <sys/event.h>
#include <sys/time.h>
#include <sys/syscall.h>	// syscall(SYS_gettid)
#else
#include <sys/epoll.h>
#endif
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>		// define int8_t ...
#include <signal.h>
#include <unistd.h>
#define closesocket close
#define ioctlsocket ioctl
#endif

#include <stdexcept>

#ifdef __GNUC__
#include <ext/hash_map>
using namespace __gnu_cxx;
namespace __gnu_cxx {
	template<> struct hash < std::string > {
		size_t operator()(const std::string& x) const {
			return hash<const char*>()(x.c_str());
		}
	};
}
#else
#include <hash_map>
using namespace stdext;
#endif

#include <stdint.h>

#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef signed char       int8_t;
typedef signed short      int16_t;
typedef signed int        int32_t;
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;
typedef signed __int64       int64_t;
typedef unsigned __int64     uint64_t;
#else
#include <stdint.h>
#endif

#ifdef _WIN32
typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef	long long			int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef	unsigned long long	uint64;
typedef int					socklen_t;
#else
typedef int	SOCKET;
typedef int BOOL;
#ifndef  __APPLE__
const int TRUE = 1;
const int FALSE = 0;
#endif
const int SOCKET_ERROR = -1;
const int INVALID_SOCKET = -1;
#endif

typedef unsigned char	uchar_t;
typedef int				net_handle_t;
typedef int				conn_handle_t;

enum {
	NETLIB_OK = 0,
	NETLIB_ERROR = -1
};

#define NETLIB_INVALID_HANDLE	-1

enum
{
	NETLIB_MSG_CONNECT = 1,
	NETLIB_MSG_CONFIRM,
	NETLIB_MSG_READ,
	NETLIB_MSG_WRITE,
	NETLIB_MSG_CLOSE,
	NETLIB_MSG_TIMER,
	NETLIB_MSG_LOOP
};

const uint32 INVALID_UINT32 = (uint32)-1;
const uint32 INVALID_VALUE = 0;

typedef void(*callback_t)(void* callback_data, uint8 msg, uint32 handle, void* pParam);

#endif
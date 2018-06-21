#include "stdafx.h"
#include "clientsocket.h"

#include <Windows.h>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <locale>
#include <cctype>
#include <sys/stat.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

#pragma warning (disable: 4996) 

#define HTTP_CLIENT_EXPORT	//导出标识

#define PTR_BOOL(p)		{assert(p); if(!p){return false;}}
#define SAFE_DELETE(p)	{if(p) {delete p; p = 0;}}

const int	kmax_file_buffer_size = 10240;	//上传下载文件的buffer的大小
const int	kmax_buffer_size = 1024;	//普通传输的buffer大小
const int	kmax_http_pool_threads_num = 5;

#pragma   comment(lib,"Wsock32.lib")

namespace SocketHelper
{

	void	initializeWinSocket()
	{
		static bool initialization = false;
		if (!initialization)
		{
			WSADATA wsd;
			initialization = (WSAStartup(MAKEWORD(1, 1), &wsd) != 0);
		}
	}

	bool	setSocketBlockingState(int handle, bool block)
	{
		u_long nonBlocking = block ? 0 : 1;

		return  (ioctlsocket(handle, FIONBIO, &nonBlocking) == 0);
	}

	int waitForReadiness(int handle, bool for_ready, int timeout_msecs)
	{
		struct timeval timeout;
		struct timeval* timeoutp;

		if (timeout_msecs >= 0)
		{
			timeout.tv_sec = timeout_msecs / 1000;
			timeout.tv_usec = (timeout_msecs % 1000) * 1000;
			timeoutp = &timeout;
		}
		else
		{
			timeoutp = 0;
		}

		fd_set rset, wset;
		FD_ZERO(&rset);
		FD_SET(handle, &rset);
		FD_ZERO(&wset);
		FD_SET(handle, &wset);

		fd_set* const prset = for_ready ? &rset : 0;
		fd_set* const pwset = for_ready ? 0 : &wset;

		if (select(handle + 1, prset, pwset, 0, timeoutp) < 0)
			return -1;

		int opt;
		int len = sizeof(opt);

		if (getsockopt(handle, SOL_SOCKET, SO_ERROR, (char*)&opt, &len) < 0
			|| opt != 0)
			return -1;


		if ((for_ready && FD_ISSET(handle, &rset))
			|| ((!for_ready) && FD_ISSET(handle, &wset)))
			return 1;

		return 0;
	}

	bool	resetSocketOptions(int handle)
	{
		const int sndBufSize = 65536;
		const int rcvBufSize = 65536;
		const int one = 1;

		return handle > 0
			&& setsockopt(handle, SOL_SOCKET, SO_RCVBUF, (const char*)&rcvBufSize, sizeof(rcvBufSize)) == 0
			&& setsockopt(handle, SOL_SOCKET, SO_SNDBUF, (const char*)&sndBufSize, sizeof(sndBufSize)) == 0;
	}

	bool	connectSocket(int volatile& handle, const std::string& remote_host_name,
		int remote_port_number, int timeout_millisecs)
	{
		struct hostent* const host_ent = gethostbyname(remote_host_name.c_str());

		if (host_ent == 0)
			return false;

		struct in_addr target_address;
		memcpy(&target_address.s_addr,
			*(host_ent->h_addr_list),
			sizeof(target_address.s_addr));

		struct sockaddr_in server_temp_address;
		memset(&server_temp_address, 0, sizeof(sockaddr_in));
		server_temp_address.sin_family = PF_INET;
		server_temp_address.sin_addr = target_address;
		server_temp_address.sin_port = htons((u_short)remote_port_number);

		if (handle < 0)
			handle = (int)socket(AF_INET, SOCK_STREAM, 0);

		if (handle < 0)
			return false;

		setSocketBlockingState(handle, false);

		const int result = ::connect(handle, (struct sockaddr*) &server_temp_address, sizeof(struct sockaddr_in));

		if (result < 0)
		{

			if (result == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
			{
				if (waitForReadiness(handle, false, timeout_millisecs) != 1)
				{
					setSocketBlockingState(handle, true);
					return false;
				}
			}
		}

		setSocketBlockingState(handle, true);
		resetSocketOptions(handle);

		return true;
	}

	int		readSocket(int handle, bool connected, char* dest_buffer, int max_read_length, bool block_util_all_arrived)
	{
		int bytes_read = 0;

		while (bytes_read < max_read_length)
		{
			int bytes_this_time;

			bytes_this_time = recv(handle, dest_buffer + bytes_read, max_read_length - bytes_read, 0);

			if (bytes_this_time <= 0 || !connected)
			{
				if (bytes_read == 0)
					bytes_read = -1;

				break;
			}

			bytes_read += bytes_this_time;

			if (!block_util_all_arrived)
				break;

		}

		return bytes_read;
	}

	int		writeSocket(int handle, const char* source_buffer, int max_write_length)
	{
		return send(handle, source_buffer, max_write_length, 0);
	}

	unsigned long	getIntAddress(const char* ip_address)
	{
		unsigned long ret = INADDR_NONE;
		if (ip_address)
		{
			ret = ::inet_addr(ip_address);
			if (ret == INADDR_NONE)		//是域名
			{
				struct hostent* host = gethostbyname(ip_address);
				if (host == 0)
				{
					return INADDR_NONE;
				}
				CopyMemory(&ret, host->h_addr_list[0], host->h_length);
			}
		}
		return ret;
	}
}

void InitializeWinSocket()
{
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(2, 2);
	int err;
	err = ::WSAStartup(myVersionRequest, &wsaData);
	if (!err) {
		printf("已打开套接字\n");
	}
	else {
		printf("ERROR:嵌套字未打开!");
	}
}

void UnInitializeWinSocket()
{
	WSACleanup();
}

TcpSocket::TcpSocket()
{

}

TcpSocket::~TcpSocket()
{
	close();
}

bool TcpSocket::connect(const std::string& remote_host_name, int remote_port_number, int timeout /*= 3000*/)
{
	close();

	_host_name = remote_host_name;
	_port_number = remote_port_number;

	_connected = SocketHelper::connectSocket(_handle, _host_name, _port_number, timeout);

	if (!(_connected && resetSocketOptions()))
	{
		return false;
	}
	return true;
}

void TcpSocket::close()
{
	if (_connected || _handle != SOCKET_ERROR)
	{
		closesocket(_handle);
	}
	_connected = false;
	_host_name = "";
	_port_number = 0;
	_handle = -1;
}

int TcpSocket::read(char* dest_buffer, int max_read_length)
{
	return _connected ? SocketHelper::readSocket(_handle, _connected, dest_buffer, max_read_length, false) :-1;
}

int TcpSocket::write(const char* source_buffer, int max_write_length)
{
	return _connected ? SocketHelper::writeSocket(_handle, source_buffer, max_write_length) : -1;
}

bool TcpSocket::writeAll(const char* source_buffer, int max_write_length)
{
	int unsend_data_length = max_write_length;
	const	char*	data = source_buffer;

	while (unsend_data_length)
	{
		int ret = write(data, unsend_data_length);
		if (ret <= 0)
		{
			break;
		}
		else
		{
			unsend_data_length -= ret;
			data += ret;
		}

	}
	return unsend_data_length == 0;
}

bool TcpSocket::resetSocketOptions()
{
	return	SocketHelper::resetSocketOptions(_handle);
}

UdpSocket::UdpSocket()
	:_handle(0)
{
	_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

UdpSocket::~UdpSocket()
{
	closesocket(_handle);
}

bool UdpSocket::send(const std::string& remote_host_name, int remote_port_number, const char* pbuffer, int nbuffer)
{
	if (INVALID_SOCKET == _handle) {
		return false;
	}

	struct hostent* const host_ent = gethostbyname(remote_host_name.c_str());

	if (host_ent == 0)
		return false;

	struct in_addr target_address;
	memcpy(&target_address.s_addr,*(host_ent->h_addr_list),sizeof(target_address.s_addr));

	struct sockaddr_in server_temp_address;
	memset(&server_temp_address, 0, sizeof(sockaddr_in));
	server_temp_address.sin_family = AF_INET;
	server_temp_address.sin_addr = target_address;
	server_temp_address.sin_port = htons((u_short)remote_port_number);

	int iResult = sendto(_handle, pbuffer, nbuffer, 0, (SOCKADDR *)& server_temp_address, sizeof(server_temp_address));
	if (iResult == SOCKET_ERROR) {
		int n = GetLastError();
		return false;
	}
	return true;
}

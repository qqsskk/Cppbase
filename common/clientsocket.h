#pragma once

class TcpSocket
{
public:
	TcpSocket();
	~TcpSocket();
public:
	bool connect(const std::string& remote_host_name,
		int remote_port_number,
		int timeout = 3000);
	void close();
	bool isConnected() const { return _connected; }
	int	read(char* dest_buffer, int max_read_length);
	int	write(const char* source_buffer, int max_write_length);
	bool writeAll(const char* source_buffer, int max_write_length);
private:
	bool resetSocketOptions();
private:
	std::string		_host_name;				//目标地址
	int	volatile	_port_number, _handle;	//端口号，SOCKET
	bool			_connected;				//是否已连接
};

class UdpSocket
{
public:
	UdpSocket();
	~UdpSocket();
public:
	bool send(const std::string& remote_host_name,
		int remote_port_number,const char* pbuffer, int nbuffer);
private:
	int	volatile _handle;
};

void InitializeWinSocket();
void UnInitializeWinSocket();

/*
void testSendTcp() {

TcpSocket client;
if (!client.connect("127.0.0.1", 8080)){
return;
}

std::string sMsg = "hello";
char ch[2046] = { 0 };
if (!client.write(sMsg.c_str(), sMsg.size())){
return;
}

int nRet = client.read(ch, 2048);
if (nRet == SOCKET_ERROR){
return;
}
std::string strRecv;
strRecv.assign(ch, nRet);
std::cout << strRecv << std::endl;
}

void testSendUdp() {
std::string str = "hello world";
UdpSocket udp;
udp.send("127.0.0.1", 29099, str.c_str(), str.size());
}
*/

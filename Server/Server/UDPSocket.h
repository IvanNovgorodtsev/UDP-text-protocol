#pragma once
#pragma comment (lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <system_error>
#include <string>
using namespace std;

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();
	void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0);
	void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0);
	sockaddr_in RecvFrom(char* buffer, int len, int flags = 0);
	void Bind(unsigned short port);

private:
	SOCKET sock;
};
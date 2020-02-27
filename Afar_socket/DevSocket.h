#pragma once
#include "Header.h"

class Device
{
	string m_dev_name;
	char* m_ip;
	size_t m_port;
	SOCKET sock_dev;
public:
	Device(string dev_name,const char* ip,size_t port);
	int Connect();
	void Disconnect();
	Device(const Device& d);
	void Write(const char* command);
	string Read(const char* command);
};
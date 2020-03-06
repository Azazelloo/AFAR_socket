#include "DevSocket.h"

Device::Device(string dev_name, const char* ip, size_t port):m_dev_name(dev_name),m_port(port)
{
	m_ip = new char[strlen(ip)+1];
	strcpy(m_ip,ip);
}

int Device::Connect()
{
	WSADATA ws;
	sockaddr_in addr;
	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws)))
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		return -1;
	}

	if (INVALID_SOCKET == (sock_dev = socket(AF_INET, SOCK_STREAM, 0))) //____попытка создания сокета
	{
		cout << "Socket error:" << WSAGetLastError() << endl;
		return -1;
	}

	else //устанавливаем соединение
	{
		ZeroMemory(&addr, sizeof(addr)); //заполняем память нулями
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(m_ip);
		addr.sin_port = htons(m_port); //переводим порт из обычного представления в TCP/IP

		if (SOCKET_ERROR == (connect(sock_dev, (sockaddr*)&addr, sizeof(addr))))
		{
			cout << "Error connect to "<<m_ip<<"!" << endl;
			return -1;
		}
		
		return 1;
	}

}

void Device::Disconnect()
{
	closesocket(sock_dev);
	WSACleanup();

	delete m_ip;
	m_ip = nullptr;

}

void Device::Write(const char* command)
{
	if (SOCKET_ERROR == send(sock_dev, command, strlen(command), 0)) cout << "Error write: " << WSAGetLastError();
}

string Device::Read(const char* command)
{
	Write(command);

	char read_buffer[READ_BUFF_SIZE];
	int buf_size = recv(sock_dev, read_buffer, READ_BUFF_SIZE, 0);

	if (buf_size>0) return string(read_buffer, read_buffer + buf_size);

	return "Read error!";
}

Device::Device(const Device& d)
{
	m_dev_name = d.m_dev_name;
	m_port = d.m_port;
	sock_dev = d.sock_dev;

	m_ip = new char[strlen(d.m_ip) + 1];
	strcpy(m_ip, d.m_ip);
}
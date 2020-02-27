#include "Header.h"
#include "DevSocket.h"


int main(void)
{
	ifstream File("../inc/settings.ini");
	if (!File)
	{
		cout << "Error open ini!" << endl;
		return 0;
	}

	/*create vector<Device> from ini file*/
	vector<Device> v_device;
	string tmp_name;
	char* tmp_ip = new char[20];
	size_t tmp_port;
	while (!File.eof())
	{
		File >> tmp_name>>tmp_ip>>tmp_port;
		v_device.push_back(Device(tmp_name,tmp_ip,tmp_port));
	}
	File.close();
	delete[] tmp_ip;
	cout << "Start........" << endl;

	/*Connect to all devices*/
	for (size_t i=0;i<v_device.size();i++)
	{
		if (v_device[i].Connect()>0) cout << "Connect to: " << v_device[i].Read("*IDN?\n");
		else
		{
			system("pause");
			return 0;
		}
	}
	
	/*message exchange 1*/
	{
		Device g33500B(v_device[0]);
		/*commands*/

		g33500B.Disconnect();
	}

	/*delete sockets*/ 
	//_____ÒÐÅÁÓÅÒÑß ÒÅÑÒÈÐÎÂÀÍÈÅ
	/*	for (int i=v_device.size()-1;i>=0;i--)
		{
			v_device[i].Disconnect();
			v_device.pop_back();
		}*/


	/*
	N8735A.Write("*RST\n"); //_____reset
	N8735A.Write(":SYSTem:COMMunicate:RLSTate REMOTE\n"); //______block buttons
	N8735A.Write(":SOURce:VOLTage:LEVel:IMMediate:AMPLitude 24\n"); //______set voltage
	N8735A.Write(":SOURce:CURRent:LEVel:IMMediate:AMPLitude 8\n"); //______set amp
	//______output 1 ON*/
}
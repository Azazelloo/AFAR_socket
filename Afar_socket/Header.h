#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <Winsock2.h>
#include <windows.h>

#define	  stop __asm nop
#define	  READ_BUFF_SIZE 1024
using namespace std;
#pragma comment(lib,"Wsock32.lib")
#pragma once
//ws2_32.lib文件，提供了对以下网络相关API的支持，若使用其中的API，则应该将ws2_32.lib加入工程（否则需要动态载入ws2_32.dll）。
//这句话一般出现在网络编程中，需要使用网络API函数的时候，就必须使用这条语句加载ws2_32.lib库或者动态载入ws2_32.dll。
#pragma comment(lib,"ws2_32.lib")
#include "IPStruct.h"
#include <string>
using namespace std;

class CSingleton
{
public:
	CSingleton();
	~CSingleton();
	static CSingleton * GetInstance();
	SOCKET CreateSocket(DWORD dwIP, const string strMulticastAddress, int nPort);
	int OnConncet(Address *pAddress);
	int SendOut(unsigned char *pBuffer, int Len);
private:
	static CSingleton * m_pInstance;
	Address m_Address;
	SOCKET m_socket;
};


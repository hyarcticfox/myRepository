#pragma once
//ws2_32.lib�ļ����ṩ�˶������������API��֧�֣���ʹ�����е�API����Ӧ�ý�ws2_32.lib���빤�̣�������Ҫ��̬����ws2_32.dll����
//��仰һ��������������У���Ҫʹ������API������ʱ�򣬾ͱ���ʹ������������ws2_32.lib����߶�̬����ws2_32.dll��
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


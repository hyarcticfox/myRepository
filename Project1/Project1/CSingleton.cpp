#include "CSingleton.h"
#include "CNetworkPacketCodec.h"
CSingleton * CSingleton::m_pInstance = NULL;
//作用：
//static是用以控制变量的可见性和存储方式。我们知道，栈上的变量在函数结束后自动释放，而如果分配在堆上又不方便进行控制，如果定义一个全局变量会完全暴露，破坏了它的访问范围，而静态变量可以维持在一定范围内可见。
//内部机制：
//1.static变量是服务于整个类，而非某一个对象，因此它要求在程序的一开始就已经存在，而不管有没有创建属于该类的对象，因为函数是在程序的运行中被调用的，所以静态变量不能在函数中进行分配空间和初始化。
//2.这样一来，它可以进行分配空间就有三个可能的地方，一是作为类的外部接口的头文件，那里有类声明；二是类定义的内部实现，那里有类的成员函数定义；三是应用程序的main（）函数前的全局数据声明和定义处。
//3.因为类的头文件声明只对变量进行声明，而不会分配空间，所以不能在类的头文件中进行定义。
//4.如果在类的头文件声明外进行定义，可能别的类在进行引用时会出现重复定义。
//5.静态变量存储在程序的静态存储区上。
//6.这里有个例外，如果成员变量是静态常量类型的整数类（如int，char，bool），可以直接在声明中初始化，而无需定义。（From Effective C++）
//解决方法
//LINK2001的问题就是m_Singleton没有分配空间。
//因此只要在CSingleton.cpp外进行静态变量的定义就可以了。

CSingleton::CSingleton()
{
}


CSingleton::~CSingleton()
{
}

CSingleton * CSingleton::CSingleton::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CSingleton;
	}
	return m_pInstance;
}

SOCKET CSingleton::CreateSocket(DWORD dwIP, const string strMulticastAddress, int nPort)
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addSrv;
	ZeroMemory(&addSrv, sizeof(SOCKADDR_IN));
	addSrv.sin_family = AF_INET;
	addSrv.sin_port = htons(nPort);
	addSrv.sin_addr.S_un.S_addr = htonl(dwIP);
	int Ret = bind(sock, (SOCKADDR *)&addSrv, sizeof(addSrv));
	if (Ret != 0)
	{
		int errorCode = WSAGetLastError();
		closesocket(sock);
		return INVALID_SOCKET;
	}
	else
	{
		int optVal = 1024 * 1024;
		int optLen = sizeof(int);
		setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, optLen);
		//加入组播组
	/*	ip_mreq multiCast;
		multiCast.imr_interface.S_un.S_addr = inet_addr(m_commInfo.m_strLocalAddr);
		multiCast.imr_multiaddr.S_un.S_addr = inet_addr(m_commInfo.m_strMulticastAddr);
		Ret = setsockopt(sock, IPPROTO_UDP, IP_ADD_MEMBERSHIP, (char *)&multiCast, sizeof(multiCast));*/
	}
	return SOCKET();
}
int CSingleton::OnConncet(Address *pAddress)
{
	if (INVALID_SOCKET == m_socket)
	{
		memcpy(&m_Address, pAddress, sizeof(m_Address));
		m_socket = CreateSocket(m_Address.m_dwLocalIP, "", m_Address.m_nPort);
	}
	else
	{
		m_Address.m_dwLocalLogicIP = pAddress->m_dwLocalLogicIP;
		m_Address.m_dwReceiverLogicIP = pAddress->m_dwReceiverLogicIP;
	}
	return INVALID_SOCKET != m_socket;
}

int CSingleton::SendOut(unsigned char * pBuffer, int nLen)
{
	CNetworkPacketCodec NetworkPacketCodec;
	NetworkPacketCodec.EncodeDataPacket(pBuffer, nLen);
	unsigned char *pPktBuffer = NetworkPacketCodec.GetPacket();
	int nPktLen = NetworkPacketCodec.GetPacketLength();
	SOCKADDR_IN rcvAddr;
	ZeroMemory(&rcvAddr, sizeof(SOCKADDR_IN));
	rcvAddr.sin_port = htons(m_Address.m_nPort);
	rcvAddr.sin_addr.S_un.S_addr = htonl(m_Address.m_dwTransIP);
	int nRet = sendto(m_socket, (char *)pPktBuffer, nPktLen, 0, (SOCKADDR*)&rcvAddr, sizeof(SOCKADDR));
	return 0;
}

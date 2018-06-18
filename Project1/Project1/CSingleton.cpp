#include "CSingleton.h"
#include "CNetworkPacketCodec.h"
CSingleton * CSingleton::m_pInstance = NULL;
//���ã�
//static�����Կ��Ʊ����Ŀɼ��Ժʹ洢��ʽ������֪����ջ�ϵı����ں����������Զ��ͷţ�����������ڶ����ֲ�������п��ƣ��������һ��ȫ�ֱ�������ȫ��¶���ƻ������ķ��ʷ�Χ������̬��������ά����һ����Χ�ڿɼ���
//�ڲ����ƣ�
//1.static�����Ƿ����������࣬����ĳһ�����������Ҫ���ڳ����һ��ʼ���Ѿ����ڣ���������û�д������ڸ���Ķ�����Ϊ�������ڳ���������б����õģ����Ծ�̬���������ں����н��з���ռ�ͳ�ʼ����
//2.����һ���������Խ��з���ռ�����������ܵĵط���һ����Ϊ����ⲿ�ӿڵ�ͷ�ļ����������������������ඨ����ڲ�ʵ�֣���������ĳ�Ա�������壻����Ӧ�ó����main��������ǰ��ȫ�����������Ͷ��崦��
//3.��Ϊ���ͷ�ļ�����ֻ�Ա����������������������ռ䣬���Բ��������ͷ�ļ��н��ж��塣
//4.��������ͷ�ļ���������ж��壬���ܱ�����ڽ�������ʱ������ظ����塣
//5.��̬�����洢�ڳ���ľ�̬�洢���ϡ�
//6.�����и����⣬�����Ա�����Ǿ�̬�������͵������ࣨ��int��char��bool��������ֱ���������г�ʼ���������趨�塣��From Effective C++��
//�������
//LINK2001���������m_Singletonû�з���ռ䡣
//���ֻҪ��CSingleton.cpp����о�̬�����Ķ���Ϳ����ˡ�

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
		//�����鲥��
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

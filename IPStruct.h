#ifndef IPSTRUCT_H
#define IPSTRUCT_H
//����������.h�����ж����Ա��������ʱ�ᱨ�����ض������������ǹ���������ظ������˶��ͬ���࣬��ô�����û�и������ͷ�ļ�������ָʾ��#ifndef������ָʾ��#ifndef ����Ҫ��Ŀ�ľ��Ƿ�ֹͷ�ļ����ظ������ͱ��룬�������ܱ�֤ͷ�ļ�����������ļ�����ʱ���ڲ������ݲ��ᱻ��ζ������ɴ��󡣽�����������֣�


#include <windows.h>
typedef struct  
{
	DWORD m_dwLocalIP;
	DWORD m_dwTransIP;
	unsigned int m_nPort;
	DWORD m_dwLocalLogicIP;
	DWORD m_dwReceiverLogicIP;

} Address;
#endif
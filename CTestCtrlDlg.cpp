#include "CTestCtrlDlg.h"
#include <string>
#include "CSingleton.h"
using namespace std;
CTestCtrlDlg::CTestCtrlDlg()
{
	memset(&m_address, 0, sizeof(m_address));
	LoadConfig();
}


CTestCtrlDlg::~CTestCtrlDlg()
{
}

void CTestCtrlDlg::WriteConfig()
{
	FILE *file;
	if ((file = fopen("./config.txt", "w")) != NULL)
	{
		char write[200] = { 0 };
		fprintf(file, "%s", "端口号: ");
		fprintf(file, "%d\n", m_address.m_nPort);
		//关闭_CRT_SECURE_NO_WARNINGS警告，在项目->属性->C/C++->预处理器->预处理器定中添加 _CRT_SECURE_NO_WARNINGS 这个预定义。 

		sprintf(write, "%d.%d.%d.%d", m_address.m_dwLocalIP >> 24,
			m_address.m_dwLocalIP >> 16 & 0xff,
			m_address.m_dwLocalIP >> 8 & 0xff,
			m_address.m_dwLocalIP & 0xff);
		fprintf(file, "%s", "物理地址: ");
		fprintf(file, "%s\n", write);

		sprintf(write, "%d.%d.%d.%d", m_address.m_dwTransIP >> 24,
			m_address.m_dwTransIP >> 16 & 0xff,
			m_address.m_dwTransIP >> 8 & 0xff,
			m_address.m_dwTransIP & 0xff);
		fprintf(file, "%s", "传输地址: ");
		fprintf(file, "%s\n", write);

		sprintf(write, "%d.%d.%d.%d", m_address.m_dwLocalLogicIP >> 24,
			m_address.m_dwLocalLogicIP >> 16 & 0xff,
			m_address.m_dwLocalLogicIP >> 8 & 0xff,
			m_address.m_dwLocalLogicIP & 0xff);
		fprintf(file, "%s", "本机逻辑地址: ");
		fprintf(file, "%s\n", write);

		sprintf(write, "%d.%d.%d.%d", m_address.m_dwReceiverLogicIP >> 24,
			m_address.m_dwReceiverLogicIP >> 16 & 0xff,
			m_address.m_dwReceiverLogicIP >> 8 & 0xff,
			m_address.m_dwReceiverLogicIP & 0xff);
		fprintf(file, "%s", "收方逻辑地址: ");
		fprintf(file, "%s\n", write);
		fclose(file);
	}
}
void CTestCtrlDlg::LoadConfig()
{
	FILE *file = NULL;
	file = fopen("./config.txt", "r");
	if (NULL == file)
	{
		m_address.m_nPort = 0;
		m_address.m_dwLocalIP = 0x0;
		m_address.m_dwTransIP = 0x0;
		m_address.m_dwLocalLogicIP = 0x0;
		m_address.m_dwReceiverLogicIP = 0x0;

	}
	else
	{
		int i = 0;
		char read[100] = { 0 };
		fscanf(file, "%s", read);
		fscanf(file, "%s", read);
		m_address.m_nPort = atoi(read);
		fscanf(file, "%s", read);
		fscanf(file, "%s", read);
		m_address.m_dwLocalIP = htonl(inet_addr(read));
		fscanf(file, "%s", read);
		fscanf(file, "%s", read);
		m_address.m_dwTransIP = htonl(inet_addr(read));
		fscanf(file, "%s", read);
		fscanf(file, "%s", read);
		m_address.m_dwLocalLogicIP = htonl(inet_addr(read));
		fscanf(file, "%s", read);
		fscanf(file, "%s", read);
		m_address.m_dwReceiverLogicIP = htonl(inet_addr(read));
		fclose(file);
	}
}
void CTestCtrlDlg::OnClickedBtnConverse()
{
	WriteConfig();
	CSingleton::GetInstance()->OnConncet(&m_address);
	
}
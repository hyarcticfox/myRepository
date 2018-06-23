#include "CSingleton.h"
#include "CTestCtrlDlg.h"
int main()
{
	CTestCtrlDlg TestCtrlDlg;
	TestCtrlDlg.OnClickedBtnConverse();
	unsigned int nOutLen = 0;
	unsigned char chOutBuffer[2500] = { 0 };
	int nSendOutLen = CSingleton::GetInstance()->SendOut(chOutBuffer, nOutLen);
	if (nSendOutLen < 0)
	{
		
		int Error = WSAGetLastError();
	}
	return 0;
}
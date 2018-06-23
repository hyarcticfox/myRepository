#pragma once
#include "IPStruct.h"
class CTestCtrlDlg
{
public:
	CTestCtrlDlg();
	~CTestCtrlDlg();
	Address m_address;
	void WriteConfig();
	void LoadConfig();
	void OnClickedBtnConverse();
};


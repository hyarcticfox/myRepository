#include "CSingleton.h"

int main()
{
	unsigned int nOutLen = 0;
	unsigned char chOutBuffer[2500] = { 0 };
	int nSendOutLen = CSingleton::GetInstance()->SendOut(chOutBuffer, nOutLen);
	if (nSendOutLen < 0)
	{
		
		int Error = WSAGetLastError();
	}
	return 0;
}
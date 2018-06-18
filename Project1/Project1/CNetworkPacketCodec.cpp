#include "CNetworkPacketCodec.h"
#define DATA_MAX 100
#include <string.h>

CNetworkPacketCodec::CNetworkPacketCodec()
{
}


CNetworkPacketCodec::~CNetworkPacketCodec()
{
}

void CNetworkPacketCodec::SetData(unsigned char * pDataBuffer, unsigned int nDataLen)
{
	if(nDataLen<=0||nDataLen>DATA_MAX)
	{
		return;
	}
	memcpy(m_pDataBuffer, pDataBuffer, nDataLen);
	m_nDataLen = nDataLen;
}

void CNetworkPacketCodec::EncodeDataPacket(unsigned char * pDataArea, unsigned int nDataLen)
{
	SetData(pDataArea, nDataLen);
}

unsigned char * CNetworkPacketCodec::GetDataArea() const
{
	return m_pDataBuffer;
}

unsigned char * CNetworkPacketCodec::GetPacket() const
{
	return m_pPacketBuffer;
}

unsigned int CNetworkPacketCodec::GetDataLength() const
{
	return m_nDataLen;
}

unsigned int CNetworkPacketCodec::GetPacketLength() const
{
	return m_nPacketLen;
}

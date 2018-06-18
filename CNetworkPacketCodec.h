#pragma once
class CNetworkPacketCodec
{
public:
	CNetworkPacketCodec();
	~CNetworkPacketCodec();
	void SetData(unsigned char * pDataBuffer, unsigned int nDataLen);
	void EncodeDataPacket(unsigned char * pDataArea, unsigned int nDataLen);
	unsigned char * GetDataArea() const;
	unsigned char * GetPacket() const;
	unsigned int GetDataLength() const;
	unsigned int GetPacketLength() const;
protected:
	unsigned char * m_pDataBuffer;
	unsigned int m_nDataLen;
	unsigned char * m_pPacketBuffer;
	unsigned int m_nPacketLen;
};


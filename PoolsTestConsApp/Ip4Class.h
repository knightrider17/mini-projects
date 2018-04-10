#pragma once

#include "helpers.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS FOR IP4 PRESENTATION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
class Ip4
{
private:
	uint8_t m_ip_1, m_ip_2, m_ip_3, m_ip_4;

public:
	Ip4() : m_ip_1(0), m_ip_2(0), m_ip_3(0), m_ip_4(0)
	{}

	Ip4(uint8_t _ip_4, uint8_t _ip_3, uint8_t _ip_2, uint8_t _ip_1)
	{
		this->m_ip_4 = _ip_4;
		this->m_ip_3 = _ip_3;
		this->m_ip_2 = _ip_2;
		this->m_ip_1 = _ip_1;
	}

	uint32_t getUint32()
	{
		return this->m_ip_1 + this->m_ip_2 * 256 + this->m_ip_3 * 256 * 256 + this->m_ip_4 * 256 * 256 * 256;
	}

	void setIp4(uint32_t _ipAddressNum)
	{
		if (_ipAddressNum)
		{
			this->m_ip_1 = _ipAddressNum >> 0;
			this->m_ip_2 = _ipAddressNum >> 8;
			this->m_ip_3 = _ipAddressNum >> 16;
			this->m_ip_4 = _ipAddressNum >> 24;
		}
	}

	void printUint32()
	{
		cout << this->getUint32() << endl;
	}

	void printIp4()
	{
		cout << this->m_ip_4 << "." << this->m_ip_3 << "." << this->m_ip_2 << "." << this->m_ip_1 << endl;
	}
};
//*/

class Ip4
{
private:
	uint8_t m_ip_1, m_ip_2, m_ip_3, m_ip_4;

public:
	Ip4() : m_ip_1(0), m_ip_2(0), m_ip_3(0), m_ip_4(0)
	{}

	Ip4(uint8_t _ip_4, uint8_t _ip_3, uint8_t _ip_2, uint8_t _ip_1);
	
	uint32_t getUint32();

	void setIp4(uint32_t _ipAddressNum);

	void printUint32();

	void printIp4();
};




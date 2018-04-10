#include "Ip4Class.h"


uint32_t Ip4::getUint32()
{
	return this->m_ip_1 + this->m_ip_2 * 256 + this->m_ip_3 * 256 * 256 + this->m_ip_4 * 256 * 256 * 256;
}

void Ip4::setIp4(uint32_t _ipAddressNum)
{
	if (_ipAddressNum)
	{
		this->m_ip_1 = _ipAddressNum >> 0;
		this->m_ip_2 = _ipAddressNum >> 8;
		this->m_ip_3 = _ipAddressNum >> 16;
		this->m_ip_4 = _ipAddressNum >> 24;
	}
}

void Ip4::printUint32()
{
	cout << this->getUint32() << endl;
}

void Ip4::printIp4()
{
	cout << this->m_ip_4 << "." << this->m_ip_3 << "." << this->m_ip_2 << "." << this->m_ip_1 << endl;
}


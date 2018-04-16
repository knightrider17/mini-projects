#include <iostream>

//
// TASK_BITS_COUNTER
// ������ �������� ������������ (������) ��� � �������
//

//
// 1. ���� ������� ��������� �������� ���� ������, 
// ���� ������� ��� ������ ���������� ��������� ��������.
//
size_t getBits(unsigned char _byte)
{
	size_t count = 0;

	for (int i = 0; i < 8; ++i)
	{
		if (_byte & 0x01)
		{
			count++;
		}

		_byte = _byte >> 1;
	}

	return count;
}

//
// 2. ���� ������� ������ �������� ��������.
//
size_t getBits2(unsigned char _byte)
{
	size_t count = 0;
	unsigned char bit = 0x01;

	for (int i = 0; i < 8; ++i)
	{
		if (_byte & bit)
		{
			count++;
		}

		bit = bit << 1;
	}

	return count;
}


size_t demo(unsigned char* array, size_t length)
{
	size_t res = 0;

	for (int i = 0; i < length; ++i)
	{
		res += getBits2(array[i]);
	}

	return res;
}


void main()
{
	// 4 ���� �������.   // 001  111
	unsigned char array[] = { 1, 7 }; 

	std::cout << "Number of bits is: " << demo(array, 2) << std::endl;

	getchar();
}

#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

#include <vector>

using namespace std;


#define SOLUTION_BICYCLE 0
#define SOLUTION_STL	 1 

// ����������� ��������� ���� ��� IP-�������, ���������� � �����:
using IPAddress = uint32_t; 				// ����� IPv4 ����������� ������������� ����� uint32_t
using Range = pair<IPAddress, IPAddress>;	// �������� IP-�������, ������� ��������
using Pool = vector<Range>;					// ����� �������� � ������ ������������ STL-��������� ��� �������� ���������� IP-������� (Range)
//using Pool = ; // ? // 
											// ��������� IP-������� � ����� ����� ������������. ������� �� ������������ � ���� - ������������.

										// �������, ����������� ������� ����� ������ � ����� ������:
										// `old_pool` - ������ ��� IP-�������
										// `new_pool` - �����  ��� IP-�������
										// return value - ��� ���������� "����������" IP-�������




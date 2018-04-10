#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

#include <vector>

using namespace std;


#define SOLUTION_BICYCLE 0
#define SOLUTION_STL	 1 

// Используйте следующие типы для IP-адресов, диапазонов и пулов:
using IPAddress = uint32_t; 				// Адрес IPv4 представлен целочисленным типом uint32_t
using Range = pair<IPAddress, IPAddress>;	// Диапазон IP-адресов, границы включены
using Pool = vector<Range>;					// стоит подумать о выборе оптимального STL-котейнера для хранения диапазонов IP-адресов (Range)
//using Pool = ; // ? // 
											// Диапазоны IP-адресов в пулах могут пересекаться. Порядок их расположения в пуле - произвольный.

										// Функция, вычисляющая разницу между старым и новым пулами:
										// `old_pool` - старый пул IP-адресов
										// `new_pool` - новый  пул IP-адресов
										// return value - пул диапазонов "устаревших" IP-адресов




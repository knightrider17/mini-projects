//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREPARED FUNCTIONS FOR // SOLUTION 2 //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
// === - новый диапазон  [n1 n2]
// ^^^ - старый диапазон [o1 o2]

//                     ===========
//                         ^^^					1) старый внутри нового полностью
//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

// 1)  if(n1 <= o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> o  входит в  n
// 2)  if(n1  > o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> получаем часть диапазона [от о1   до n1-1]
// 3)  if(n1 <= o1 && n1 <= o2 && n2 <= o1 && n2 >  o2)	=> получаем часть диапазона [от n2+1 до   o2]
// 4)  if(n1  > o1 && n2 < o2)							=> о  перекрывает собой  n
// 5)  if(n1  > o1 && n2 < o2)							=> старый не входит целиком и лежит от новго слева
// 6)  if(n1  < o1 && n2 < o2)							=> --..-- и лежит от нового справа
//
// 1) if(it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> it  перекрывает собой  _r (_r уже или равно it)
// 2) if(it->first  > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> получаем часть диапазона [от _r.first   до it->first-1]
// 3) if(it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	=> получаем часть диапазона [от it->second+1 до   _r.second]
// 4) if(it->first  > _r.first && it->second < _r.second)														=> _r  перекрывает собой  it (_r больше it)
// 5+6)if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) 
//		=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

#include "solutionBicycle.h"

#if SOLUTION_BICYCLE

void includeRangeToPool(Pool& _pool, Range _r)
{
	// строго говоря перед добавлением мы должны склеить все пересекающиеся диапазоны
	bool isAdded = false;
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// _r-ки нужно прикреплять к it-am или добавлять полностью в контейнер

		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> it  перекрывает собой  _r (_r уже или равно it)
		{   //отметим как добавленный, и не будем добавлять в пул
			isAdded = true; // уже содержится в каком-то диапазоне
			break;
		}
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> получаем часть диапазона [от _r.first   до it->first-1]
		{
			Range bigger_left(_r.first, it->second);
			_pool.erase(it);
			_pool.push_back(bigger_left);
			isAdded = true;
			break;
		}
		if (it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	//=> получаем часть диапазона [от it->second+1 до   _r.second]
		{
			Range bigger_right(it->first, _r.second);
			_pool.erase(it);
			_pool.push_back(bigger_right);
			isAdded = true;
			break;
		}
		if (it->first >= _r.first && it->second <= _r.second)															//=> _r  перекрывает собой  it (_r больше it)
		{	//заменим один на другой / "сольём" их воедино
			_pool.erase(it);
			_pool.push_back(_r);
			isAdded = true;
			break;
		}

		// мы объединяем, так что то, что за пределами мы включаем в итоговый пул через  if (см. ниже за пределами цикла (*) )
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

		++it;
	}

	// добавляем элементы в кнтрейнер в случаях, когда:
	// контейнер ещё пуст
	// или мы его ни с кем не объединили, хоть и прошли его от начала и до конца
	if ((!isAdded) && (it == _pool.end())) // (*)
	{
		_pool.push_back(_r);
	}
}

void excludeRangeFromPool(Pool& _pool, Range _r)
{
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// _r-ки нужно вырезать из it-ов

		if ((it->first <= _r.first) && (it->first <= _r.second) && (it->second >= _r.first) && (it->second >= _r.second))	//=> it  перекрывает собой  _r (_r уже или равно it)
		{   // вырежем посерёдке стоящий _r и оставим 2 куска оставшихся от it ИЛИ (...)
			Range part_left, part_right;
			uint32_t it_first(it->first), it_second(it->second);

			if (it->first != _r.first)
			{
				part_left = Range(it->first, _r.first - 1);
			}
			if (it->second != _r.second)
			{
				part_right = Range(_r.second + 1, it->second);
			}

			_pool.erase(it); // (...) ИЛИ удалим весь элемент, ничего не добавляя, если диапазоны совпали

			if (it_first != _r.first)
			{
				_pool.push_back(part_left);
			}
			if (it_second != _r.second)
			{
				_pool.push_back(part_right);
			}

			break;
		}
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> оставляем [от _r.second+1   до it->second]
		{								 //      o1......o2
			if (it->second != _r.second) // n1.......n2
			{
				Range part_right(_r.second + 1, it->second);
				_pool.erase(it);
				_pool.push_back(part_right);
			}
			else						//      o1..o2
			{							// n1.......n2
				_pool.erase(it);
			}

			break;
		}
		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second <  _r.second)	//=> получаем часть диапазона [от it->first до   _r.first - 1]
		{
			if (it->first != _r.first)
			{
				Range part_left(it->first, _r.first - 1);
				_pool.erase(it);
				_pool.push_back(part_left);
			}
			else
			{
				_pool.erase(it);
			}

			break;
		}
		if (it->first  > _r.first && it->second < _r.second)															//=> _r  перекрывает собой  it (_r больше it)
		{	// удаляем элемент полностью
			_pool.erase(it);
			break;
		}
		// мы вырезаем, а то, что за пределами мы итак не вырежем
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

		++it;
	}
}

// Pool = vector<pair<uint32_t, uint32_t>>
//*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SOLUTION 2: // MY own BICYCLE Solution
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pool find_diff(const Pool& _old_pool, const Pool& _new_pool)
{
	Pool result_pool;

	Pool merged_old_pool;
	for (auto& old_item : _old_pool)
		includeRangeToPool(merged_old_pool, old_item);

	Pool merged_new_pool;
	for (auto& new_item : _new_pool)
		includeRangeToPool(merged_new_pool, new_item);

	// Убрать из всех старых все новые и оставить "устаревшие"
	for (auto& new_item : merged_new_pool)
	{
		for (int i = 0, ilen = merged_old_pool.size(); i < ilen; i++)
		{
			excludeRangeFromPool(merged_old_pool, new_item);
			if (merged_old_pool.size() > ilen)
				ilen = merged_old_pool.size();
		}
	}

	result_pool = merged_old_pool;
	return result_pool;
}
//*/

#endif

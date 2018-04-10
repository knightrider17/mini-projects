//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREPARED FUNCTIONS FOR // SOLUTION 2 //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��������� ��������� ��������� / ����������� ���������� ���� � ������ ����� 6:
// === - ����� ��������  [n1 n2]
// ^^^ - ������ �������� [o1 o2]

//                     ===========
//                         ^^^					1) ������ ������ ������ ���������
//                   ^^^^       ^^^^			2) ������ �� ������ � ����� ����� 3) ������ �� ������ � ����� ������
//               ^^^^^^^^^^^^^^^^^^^^^^^		4) ������ �� ������ � ����� � ����� � ������
//         ^^^^                           ^^^^	5) ������ �� ������ ������� � ����� �� ����� ����� 6) --..-- � ����� �� ������ ������

// 1)  if(n1 <= o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> o  ������ �  n
// 2)  if(n1  > o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> �������� ����� ��������� [�� �1   �� n1-1]
// 3)  if(n1 <= o1 && n1 <= o2 && n2 <= o1 && n2 >  o2)	=> �������� ����� ��������� [�� n2+1 ��   o2]
// 4)  if(n1  > o1 && n2 < o2)							=> �  ����������� �����  n
// 5)  if(n1  > o1 && n2 < o2)							=> ������ �� ������ ������� � ����� �� ����� �����
// 6)  if(n1  < o1 && n2 < o2)							=> --..-- � ����� �� ������ ������
//
// 1) if(it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> it  ����������� �����  _r (_r ��� ��� ����� it)
// 2) if(it->first  > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> �������� ����� ��������� [�� _r.first   �� it->first-1]
// 3) if(it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	=> �������� ����� ��������� [�� it->second+1 ��   _r.second]
// 4) if(it->first  > _r.first && it->second < _r.second)														=> _r  ����������� �����  it (_r ������ it)
// 5+6)if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) 
//		=> _r ��������� �� ��������� � �� ������������ � it �� � ���� �� ������, �� � ��������

#include "solutionBicycle.h"

#if SOLUTION_BICYCLE

void includeRangeToPool(Pool& _pool, Range _r)
{
	// ������ ������ ����� ����������� �� ������ ������� ��� �������������� ���������
	bool isAdded = false;
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// _r-�� ����� ����������� � it-am ��� ��������� ��������� � ���������

		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> it  ����������� �����  _r (_r ��� ��� ����� it)
		{   //������� ��� �����������, � �� ����� ��������� � ���
			isAdded = true; // ��� ���������� � �����-�� ���������
			break;
		}
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> �������� ����� ��������� [�� _r.first   �� it->first-1]
		{
			Range bigger_left(_r.first, it->second);
			_pool.erase(it);
			_pool.push_back(bigger_left);
			isAdded = true;
			break;
		}
		if (it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	//=> �������� ����� ��������� [�� it->second+1 ��   _r.second]
		{
			Range bigger_right(it->first, _r.second);
			_pool.erase(it);
			_pool.push_back(bigger_right);
			isAdded = true;
			break;
		}
		if (it->first >= _r.first && it->second <= _r.second)															//=> _r  ����������� �����  it (_r ������ it)
		{	//������� ���� �� ������ / "������" �� �������
			_pool.erase(it);
			_pool.push_back(_r);
			isAdded = true;
			break;
		}

		// �� ����������, ��� ��� ��, ��� �� ��������� �� �������� � �������� ��� �����  if (��. ���� �� ��������� ����� (*) )
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r ��������� �� ��������� � �� ������������ � it �� � ���� �� ������, �� � ��������

		++it;
	}

	// ��������� �������� � ��������� � �������, �����:
	// ��������� ��� ����
	// ��� �� ��� �� � ��� �� ����������, ���� � ������ ��� �� ������ � �� �����
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
		// _r-�� ����� �������� �� it-��

		if ((it->first <= _r.first) && (it->first <= _r.second) && (it->second >= _r.first) && (it->second >= _r.second))	//=> it  ����������� �����  _r (_r ��� ��� ����� it)
		{   // ������� �������� ������� _r � ������� 2 ����� ���������� �� it ��� (...)
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

			_pool.erase(it); // (...) ��� ������ ���� �������, ������ �� ��������, ���� ��������� �������

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
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> ��������� [�� _r.second+1   �� it->second]
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
		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second <  _r.second)	//=> �������� ����� ��������� [�� it->first ��   _r.first - 1]
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
		if (it->first  > _r.first && it->second < _r.second)															//=> _r  ����������� �����  it (_r ������ it)
		{	// ������� ������� ���������
			_pool.erase(it);
			break;
		}
		// �� ��������, � ��, ��� �� ��������� �� ���� �� �������
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r ��������� �� ��������� � �� ������������ � it �� � ���� �� ������, �� � ��������

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

	// ������ �� ���� ������ ��� ����� � �������� "����������"
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

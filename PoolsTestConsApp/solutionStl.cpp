//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREPARED FUNCTIONS FOR // SOLUTION 1 //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "solutionStl.h"


#if SOLUTION_STL

bool predicate_fun(IPAddress _ip_1, IPAddress _ip_2)
{
	return _ip_1 < _ip_2;
}

// заполним из   _pool_from   в    _pool_to
void fillVVectorFromPool(const Pool& _pool_from, vector<vector<IPAddress>>& _pool_to)
{
	for (auto& it_range : _pool_from)
	{
		vector<IPAddress> diapason;
		for (IPAddress i = it_range.first, ilen = it_range.second; i <= ilen; i++)
			diapason.push_back(i);

		sort(diapason.begin(), diapason.end(), predicate_fun);
		_pool_to.push_back(diapason);
	}
}

// заполним из   _pool_from   в    _pool_to
void fillPoolFromVVector(vector<vector<IPAddress>>& _pool_from, Pool& _pool_to)
{
	// отработает, даже если элемент в it_vrange всего один, просто добавитс€ диапазон [ххх ; ххх]
	for (auto& it_vrange : _pool_from)
		_pool_to.push_back(Range(it_vrange[0], it_vrange[it_vrange.size() - 1]));
}


// Pool = vector<pair<uint32_t, uint32_t>>
//*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SOLUTION 1: // STL-–ешение использу€ SET_DIFFERENCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pool find_diff(const Pool& _old_pool, const Pool& _new_pool)
{
	Pool result_pool;

	vector<vector<IPAddress>> old_pool;
	fillVVectorFromPool(_old_pool, old_pool);

	vector<vector<IPAddress>> new_pool;
	fillVVectorFromPool(_new_pool, new_pool);

	vector<vector<IPAddress>> diff_result;
	vector<vector<IPAddress>> old_pool_cut(old_pool);
	while(true)
	{
		bool foundBetween = false;
		uint32_t old_pool_i = 0;
		old_pool = old_pool_cut;
		diff_result.clear();

		for (auto old_item : old_pool)
		{
			vector<IPAddress> diff;
			for (auto& new_item : new_pool)
			{
				diff.clear();
				// set_difference флгоритм всЄ сделает за нас
				vector<IPAddress>::iterator it;
				set_difference(old_item.begin(), old_item.end(),
					new_item.begin(), new_item.end(),
					inserter(diff, diff.begin()), predicate_fun);
				
				if (diff.size() < old_item.size())
				{
					// особенность работы set_difference дл€ случа€ с old=123456 пересечением всередине new=34 
					// результат помещаетс€ не в 2 выходных объекта  [12] [56], а в один и они идут друг за другом [1256]
					if (!diff.empty())
					{
						if (old_item[0] == diff[0] && old_item[old_item.size() - 1] == diff[diff.size() - 1])
						{
							ptrdiff_t pos = find(old_item.begin(), old_item.end(), new_item[0]) - old_item.begin();
							if (pos > 0)
							{
								// удалим из dif "правую" часть:
								diff.erase(diff.begin() + pos, diff.end());
								// удалим из old "левую" часть:
								old_item.erase(old_item.begin(), old_item.begin() + pos + new_item.size());

								old_pool.erase(old_pool.begin() + old_pool_i);
								old_pool_cut = old_pool;
								old_pool_cut.push_back(diff);
								old_pool_cut.push_back(old_item);
								foundBetween = true;
								break;
							}
						}
					}

					old_item = diff;
					if (old_item.empty() || diff.empty())
						break;
				}
			}

			if (foundBetween)
				break;

			if (!old_item.empty())
			{
				diff_result.push_back(old_item);
			}
			old_pool_i++;
		}

		if (!foundBetween && (old_pool_i == old_pool.size()))
		{
			break;
		}
	}

	//for (auto& diap : diff_result)
	//{
	//	for (auto& ip : diap)
	//		cout << ip;
	//}

	fillPoolFromVVector(diff_result, result_pool);

	return result_pool;
}
//*/

#endif

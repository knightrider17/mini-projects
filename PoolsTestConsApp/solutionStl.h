#pragma once

#include "helpers.h"

#if SOLUTION_STL

bool predicate_fun(IPAddress _ip_1, IPAddress _ip_2);

void fillVVectorFromPool(const Pool& _pool_from, vector<vector<IPAddress>>& _pool_to);
void fillPoolFromVVector(vector<vector<IPAddress>>& _pool_from, Pool& _pool_to);
Pool find_diff(const Pool& _old_pool, const Pool& _new_pool);

#endif

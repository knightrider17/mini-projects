#pragma once

#include "helpers.h"

#if SOLUTION_BICYCLE

void includeRangeToPool(Pool& _pool, Range _r);
void excludeRangeFromPool(Pool& _pool, Range _r);
Pool find_diff(const Pool& _old_pool, const Pool& _new_pool);

#endif
#include "tests.h"

#include "main.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// внутри "helpers.h"  смените define-ное  SOLUTION_BICYCLE на SOLUTION_STL чтобы запустить второе решение 

void main()
{
	test_1_pools();			// 1

	test_2_pools();			// 2
	test_2_inverse_pools();	// 3
	
	test_3_pools();			// 4
	test_3_inverse_pools();	// 5

	test_4_pools();			// 6
	test_4_inverse_pools();	// 7

	test_5_pools();			// 8
	test_5_inverse_pools(); // 9

	test_6_pools();			// 10
	test_7_pools();			// 11

	test_8_pools();			// 12
	test_8_inverse_pools();	// 13

	getchar();
}
#include "tests.h"
#include "solutionBicycle.h"
#include "solutionStl.h"


void fillPoolFromArray(vector<uint8_t> &_arr_from, Pool& _pool_to)
{
	for (size_t i = 0, ilen = _arr_from.size(); i < ilen; i += 2)
	{
		_pool_to.push_back(Range(_arr_from[i], _arr_from[i + 1]));
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRINT FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_test_line(const std::string _test_name)
{
	std::cout << "========================" << _test_name.c_str() << "==========================" << std::endl;
}

void print_pool(const std::string _pool_name, const Pool& _print_pool)
{
	_print_pool.empty()
		? std::cout << _pool_name.c_str() << " is EMPTY" << std::endl
		: std::cout << _pool_name.c_str() << std::endl;

	for (const auto& item : _print_pool)
	{
		std::cout << "[" << item.first << " : " << item.second << "]" << std::endl;
	}
	std::cout << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					TESTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//    1=3		4===6		10===12		  15=16  
//  0^1           5^^^8       11^12     13^^^16
//  0^^2
//  0^^^3
//    1^3
// 0,0 7,8 13,14
void test_1_pools()
{
	print_test_line("test_1");
	//vector<uint8_t> new_mas = { 5,6, 15,18 };
	//vector<uint8_t> old_mas = { 0,10, 10,20 };

	vector<uint8_t> new_mas = { 1,3, 4,6, 10,12, 15,16 };
	vector<uint8_t> old_mas = { 0,3, 0,1, 5,8, 0,2, 1,3, 11,12, 13,16 };

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);

}


//            11=========21						       40=========50   
//                15^16                                    45^46                      
//          10^12       20^22                        35^42       50^62                
//       8^^^^^^^^^^^^^^^^^^^^^24                   30^40        50^^^^72               
// 4^^6                           26^28      25^^35                     65^80         
// 4,6 8,10 10,10, 22,22 22,24 26,28 25,35  30,39 35,39 51,62 51,72 65,80
void test_2_pools()
{
	print_test_line("test_2");

	vector<uint8_t> new_mas = { 11,21, 40,50 };
	vector<uint8_t> old_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

//                                               res =  43^44 47^49
//            11^^^^^^^^^21						       40^^^^^^^^^50   
//                15=16                                    45=46                      
//          10=12       20=22                        35=42       50=62                
//       8=====================24                   30=40        50===72               
// 4==6                           26=28      25==35                     65=80     
// 43,44 47,49
void test_2_inverse_pools()
{
	print_test_line("test_2_inverse");

	vector<uint8_t> old_mas = { 11,21, 40,50 };
	vector<uint8_t> new_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}


//                   16===========================================50
//            11=========21							         
//                15^16                                    45^46                      
//          10^12       20^22                        35^42       50^62                
//       8^^^^^^^^^^^^^^^^^^^^^24                   30^40        50^^^^72               
// 4^^6                           26^28      25^^35                     65^80         
// 4,6 10,10 8,10 51,62 51,72 65,80
void test_3_pools()
{
	print_test_line("test_3");

	vector<uint8_t> new_mas = { 11,21, 16,50 };
	vector<uint8_t> old_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

// 43,44 47,49
///////////////////////////
void test_3_inverse_pools()
{
	print_test_line("test_3_inverse");

	vector<uint8_t> old_mas = { 11,21, 16,50 };
	vector<uint8_t> new_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}


//    5================================================================60
//                   16===========================================50
//					15=====================================45							         
//							20========================35							         
//									24=========30							         
//                15^16                                    45^46                      
//          10^12       20^22                        35^42       50^62                
//       8^^^^^^^^^^^^^^^^^^^^^24                   30^40        50^^^^72               
// 4^^6                           26^28      25^^35                     65^80         
// 4,4 61,62 61,72 65,80
void test_4_pools()
{
	print_test_line("test_4");

	vector<uint8_t> new_mas = { 24,30, 20,35, 15,45, 16,50, 5,60 };
	vector<uint8_t> old_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

//7,7 43,44 47,49
///////////////////////////
void test_4_inverse_pools()
{
	print_test_line("test_4_inverse");

	vector<uint8_t> old_mas = { 24,30, 20,35, 15,45, 16,50, 5,60 };
	vector<uint8_t> new_mas = { 4,6, 10,12, 15,16, 8,24, 20,22, 26,28, 30,40, 25,35, 35,42, 45,46, 50,62, 50,72, 65,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

//       5==10      20====30           40=======50            60=====65
// 4^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^80               
void test_5_pools()
{
	print_test_line("test_5");

	vector<uint8_t> new_mas = { 5,10, 20,30, 40,50, 60,65 };
	vector<uint8_t> old_mas = { 4,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

///////////////////////////
void test_5_inverse_pools()
{
	print_test_line("test_5_inverse");

	vector<uint8_t> old_mas = { 5,10, 20,30, 40,50, 60,65 };
	vector<uint8_t> new_mas = { 4,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

//  5==10              11====50                 51=51             52=====79
// 4^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^80               
void test_6_pools()
{
	print_test_line("test_6");

	vector<uint8_t> new_mas = { 5,10, 11,50, 51,51, 52,79 };
	vector<uint8_t> old_mas = { 4,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

// 4==10              11====50                 51=51             52========80
// 4^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^80               
void test_7_pools()
{
	print_test_line("test_7");

	vector<uint8_t> new_mas = { 4,10, 11,50, 51,51, 52,80 };
	vector<uint8_t> old_mas = { 4,80 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

// 4==10 12=13 14=15 16=====19   21=25 28==35    37==40  51======61  52========80 81=========================99
// 4^^10    13^14    16^^^18   20^^^25 28^^^^37   38^40     55^^60                    82^83 84^85 89^93 95^97
void test_8_pools()
{
	print_test_line("test_8");

	vector<uint8_t> new_mas = { 4,10, 12,13, 14,15, 16,19, 21,25, 28,35, 37,40, 51,61, 52,80, 81,99 };
	vector<uint8_t> old_mas = { 4,10, 13,14, 16,18, 20,25, 28,37, 38,40, 55,60, 82,83, 84,85, 89,93, 95,97 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

///////////////////////////
void test_8_inverse_pools()
{
	print_test_line("test_8_inverse");

	vector<uint8_t> old_mas = { 4,10, 12,13, 14,15, 16,19, 21,25, 28,35, 37,40, 51,61, 52,80, 81,99 };
	vector<uint8_t> new_mas = { 4,10, 13,14, 16,18, 20,25, 28,37, 38,40, 55,60, 82,83, 84,85, 89,93, 95,97 };
	size_t size_mas = 0;

	Pool old_pool;
	fillPoolFromArray(old_mas, old_pool);
	print_pool("old_pool", old_pool);

	Pool new_pool;
	fillPoolFromArray(new_mas, new_pool);
	print_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	print_pool("res_pool", res_pool);
}

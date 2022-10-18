#include "tests.hpp"

// Playground for various tests to define before compile
bool playground()
{
	LongInt a, b, res;
	a = "0x4d3c91c579c2c6216567a5241614b561addf76c4bb659e6fe7f65ff76a918c843f0458b3ef457bcd9022d78798a29462ec99c74e6674690267d3e9844251b39d";
	// a.set_sign(-1);
	b = "0x1251253a";

	std::cout << LongInt::lcm(a, b) << std::endl;
	

	return true;
}

int main()
{
	set_tests();

	int x;
	std::cout << "Test number: ";
	std::cin >> x;
	while(x != 0)
	{
		if(x == 1)
			tests_512::test_1();
		else if(x == 2)
			tests_512::test_2();
		else if(x == 3)
			tests_512::test_3();
		else if(x == 4)
			tests_512::test_4();
		else if(x == 5)
			tests_1024::test_1();
		else if(x == 6)
			tests_1024::test_2();
		else if(x == 7)
			tests_1024::test_3();
		else if(x == 8)
			tests_1024::test_4();
		else if(x == 9)
			playground();

		std::cout << "Test number: ";
		std::cin >> x;
	}

    return 0;
}
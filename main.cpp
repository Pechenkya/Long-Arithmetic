#include "tests.hpp"

// Playground for various tests to define before compile
bool playground()
{
	LongInt a, b, res;
	a = "0xC514FF44301208C3535C8C097A58024B";
	b = "0x84C88E3EE2D4F87E0970164A804D96D0971";

	std::cout << LongInt::div_stoopid(a, b) << std::endl;

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
		else if(x == 10)
			div_cmp();

		std::cout << "Test number: ";
		std::cin >> x;
	}

    return 0;
}
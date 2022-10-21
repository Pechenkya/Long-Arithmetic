#include "tests.hpp"

// Playground for various tests to define before compile
bool playground()
{
	LongInt a, b, n;
	a = "0xdaf1abda4ad4d9fe3e36a529210c2ae99b9";
	b = "0x4d3c91c579c2c6";
	n = "0x5dc";

	std::cout << a << std::endl;
	std::cout << b << std::endl;

	std::cout << a - b << std::endl;

	std::cout << "a mod b : " << a % b << std::endl;
	std::cout << "a + b mod n : " << LongInt::mod_plus(a, b, n) << std::endl;
	std::cout << "a - b mod n : " << LongInt::mod_minus(a, b, n) << std::endl;
	std::cout << "a * b mod n : " << LongInt::mod_mult(a, b, n) << std::endl;
	std::cout << "a ^ 2 mod n : " << a.mod_square(n) << std::endl;
	std::cout << "a ^ b mod n : " << a.mod_power(b, n) << std::endl;

	std::cout << std::endl;
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
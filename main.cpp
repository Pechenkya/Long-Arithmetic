#include "tests.hpp"

// Playground for various tests to define before compile
bool playground()
{
	LongInt a, b;
	a = "0x7723A9B9AFFCFCACFEF4537D2C587BA1E07EC2A27B9C907261F6461044DE2FEC26DA9BACDAC77063244D575EE788BB1145D7D09A94EC4B59859669CF8D86F454";
	a.set_sign(-1);
	b = "0x7723A9B9AFFCFCACFEF4537D2C587BA1E07EC2A27B9C907261F6461044DE2FEC26DA9BACDAC77063244D575EE788BB1145D7D09A94EC4B59859669CF8D86F454";
	
	std::cout << a / b << std::endl;

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
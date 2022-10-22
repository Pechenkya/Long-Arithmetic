#include <vector>
#include <string>

class LongInt;

// Let's create casual tests (because I have no time to add GoogleTesting :))
void parse_gen_numbers();

void set_tests();

void print_test(const std::string& test_name, const LongInt& a, const LongInt& b, const LongInt& sum,
                 const LongInt& diff, const LongInt& mult, const LongInt& mult_div,
                  const LongInt& sum_res, const LongInt& diff_res, const LongInt& mult_res,
                   const LongInt& mult_div_res);

namespace tests_512
{
	bool test_1();

    bool test_2();

    bool test_3();

    bool test_4();
}

namespace tests_1024
{
    bool test_1();

    bool test_2();

    bool test_3();

    bool test_4();
}

class gen_arr_tests
{
    static std::vector<LongInt> generated_numbers;
public:
    static bool div_cmp();
    static void get_pair(LongInt& a, LongInt& b);

    friend void parse_gen_numbers();
};


#include <bitset>

/**
 * Integer class to handle 
 * long unsigned integer numbers
 */
template<size_t length = 4096>
class LongInt
{
    // Inner structure
    std::bitset<length> binary;

public:
    LongInt();
    LongInt(int _default_num);

    LongInt operator+(const LongInt& l, const LongInt& r);
};
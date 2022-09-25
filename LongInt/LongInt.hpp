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
    // Constructors
    LongInt() = default;
    LongInt(int _default_num);
    LongInt(const std::bitset<length>& _basic_bitset);
    LongInt(const LongInt & cp);
    LongInt(LongInt && mv);

    // Basic arithmetic operations
    LongInt operator+(const LongInt& r) const;
    LongInt operator-(const LongInt& r) const;
    LongInt operator*(const LongInt& r) const;
    LongInt operator/(const LongInt& r) const;
    LongInt square() const;
    LongInt power(const LongInt& r) const;

    // Assignment operators
    LongInt& operator=(const LongInt & cp);
    LongInt& operator=(LongInt && mv);
    LongInt& operator=(int _default_num);

    // Compare operators
    bool operator==(const LongInt& r) const;
    bool operator<(const LongInt& r) const;
    bool operator>(const LongInt& r) const;
    bool operator<=(const LongInt& r) const;
    bool operator>=(const LongInt& r) const;
    operator bool() const;
};
#include <cstdint>  // fixed size integer types
#include <ostream>

#define MEMORY_BLOCK_SIZE 64

/**
 * Integer class to handle 
 * long unsigned integer numbers
 */
class LongInt
{
    uint16_t arr_size;
    uint64_t* data = nullptr;

public:
    // Constructors and destructor
    LongInt();
    LongInt(uint64_t _default_num);
    LongInt(const LongInt & cp);
    LongInt(LongInt && mv);
    ~LongInt();

    // Basic binary operations
    LongInt operator<<(uint16_t n) const;
    LongInt operator>>(uint16_t n) const;
    LongInt operator^(const LongInt& r) const;
    LongInt operator&(const LongInt& r) const;
    LongInt operator|(const LongInt& r) const;
    LongInt operator~() const;


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
    LongInt& operator=(unsigned long long _default_num);

    // Compare operators
    bool operator==(const LongInt& r) const;
    bool operator<(const LongInt& r) const;
    bool operator>(const LongInt& r) const;
    bool operator<=(const LongInt& r) const;
    bool operator>=(const LongInt& r) const;
    operator bool() const;

    // User output
    friend bool operator<<(std::ostream& out, const LongInt& num);
};

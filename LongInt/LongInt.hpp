#include <cstdint>  // fixed size integer types

// Replace with predeclaration or other stuff
#include <ostream>
#include <string>
#define BASIC_ARRAY_SIZE 2
//

/**
 * Integer class to handle 
 * long unsigned integer numbers
 */
class LongInt
{
    uint64_t* data = nullptr;
    uint16_t arr_size;

public:
    // Constructors and destructor
    LongInt();
    LongInt(uint64_t _default_num, uint16_t _mem_blocks = BASIC_ARRAY_SIZE);
    LongInt(const LongInt & cp);
    LongInt(LongInt && mv);
    ~LongInt();

    // Basic binary operations
    // LongInt operator<<(int n) const;
    // LongInt operator>>(int n) const;
    LongInt operator^(const LongInt& r) const;
    LongInt operator&(const LongInt& r) const;
    LongInt operator|(const LongInt& r) const;
    LongInt operator~() const;


    // Basic arithmetic operations
    LongInt operator+(const LongInt& r) const;
    // LongInt operator-(const LongInt& r) const;
    // LongInt operator*(const LongInt& r) const;
    // LongInt operator/(const LongInt& r) const;
    // LongInt square() const;
    // LongInt power(const LongInt& r) const;

    // Assignment operators
    LongInt& operator=(const LongInt & cp);
    LongInt& operator=(LongInt && mv);
    LongInt& operator=(unsigned long long _default_num);

    // Compare operators
    // bool operator==(const LongInt& r) const;
    // bool operator!=(const LongInt& r) const;
    // bool operator<(const LongInt& r) const;
    // bool operator>(const LongInt& r) const;
    // bool operator<=(const LongInt& r) const;
    // bool operator>=(const LongInt& r) const;
    // operator bool() const;

    // User output
    // friend std::ostream& operator<<(std::ostream& out, const LongInt& num);
    std::string to_hex() const;
    std::string to_binary() const;

    // Utility functions
    // void resize(uint16_t new_arr_size); 
    // void shrink_to_fit();
    // uint64_t* get_memory();
private:
    static char hex_char[];
};
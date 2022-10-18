#pragma once
#include <cstdint>  // fixed size integer types

// Replace with predeclaration or other stuff
#include <ostream>
#include <string>
//

/**
 * Integer class to handle 
 * long integer numbers
 */
class LongInt
{
    uint64_t* data = nullptr;
    int sign;
    uint16_t arr_size;   

public:
    // Constructors and destructor
    LongInt();
    LongInt(uint64_t _default_num_abs, uint16_t _mem_blocks = BASIC_ARRAY_SIZE, int _sign = 1);
    // LongInt(std::string hex_str);   // Converting from hexidecimal num in std::string
    LongInt(const LongInt & cp);
    LongInt(LongInt && mv);
    ~LongInt();

    // Basic binary operations
    LongInt operator<<(long long n) const;
    LongInt operator>>(long long n) const;
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
    LongInt power(const LongInt& pow, uint16_t res_mem_blocks = 64) const;

    // Assignment operators
    LongInt& operator=(const LongInt & cp);
    LongInt& operator=(LongInt && mv);
    LongInt& operator=(const std::string& hex_str);   // Converting from hexidecimal num in std::string
    LongInt& operator=(int64_t _default_num);

    // Compare operators
    bool operator==(const LongInt& r) const;
    bool operator!=(const LongInt& r) const;
    bool operator<(const LongInt& r) const;
    bool operator>(const LongInt& r) const;
    bool operator<=(const LongInt& r) const;
    bool operator>=(const LongInt& r) const;
    explicit operator bool() const;

    // User output
    friend std::ostream& operator<<(std::ostream& out, const LongInt& num);
    std::string to_hex() const;
    std::string to_binary() const;

    /* Lab 2 functionality */
    static LongInt gcd(LongInt l, LongInt r);
    static LongInt lcm(const LongInt& l, const LongInt& r);

    // Modulo arithmetic
    LongInt operator%(const LongInt& n) const;
    static LongInt mod_minus(const LongInt& l, const LongInt& r, const LongInt& n);
    static LongInt mod_plus(const LongInt& l, const LongInt& r, const LongInt& n);
    static LongInt mod_mult(const LongInt& l, const LongInt& r, const LongInt& n);
    LongInt mod_square(const LongInt& n);
    LongInt mod_power(const LongInt& pow, const LongInt& n) const;

    // Additional
    static LongInt div_stoopid(LongInt l, LongInt r);
    /* ------------------- */

    // Utility functions
    void switch_sign();
    void resize(uint16_t new_arr_size); 
    void shrink_to_fit();
    uint64_t* get_memory();
    uint16_t get_arr_size() const;
    LongInt& make_abs();
// private:
    void set_sign(int _s);
private:
    // Inner structure
    uint16_t empty_upper_blocks() const;
    static bool set_longer_and_shorter(const LongInt* & a, const LongInt* & b);
    static uint16_t pref_zeroes(uint64_t val);
    void l_shift_to(LongInt& target, uint16_t loc_shift, uint16_t glob_shift) const;
    void r_shift_to(LongInt& target, uint16_t loc_shift, uint16_t glob_shift) const;

    static LongInt add_data(const LongInt& left, const LongInt& right);
    static LongInt sub_data(const LongInt& left, const LongInt& right);
    static bool cmp_data_less(const LongInt& left, const LongInt& right);

    static LongInt karatsuba_data_mult(const LongInt& a, const LongInt& b, const uint16_t& result_size);
    static LongInt mult_of_64bit(uint64_t a, uint64_t b, const uint16_t& result_size);
    static void fill_with_datacp(LongInt& to, const LongInt& from, uint16_t shift);
    static uint16_t log2_i16b(uint16_t n);

    static LongInt shift_substract(LongInt a, LongInt b);
    uint32_t bit_length() const;

    /* Lab 2 functionality */
    static LongInt barrett_precalc(const LongInt& n);
    static LongInt barrett_reduction(const LongInt& x, const LongInt& n, const LongInt& mi);
    /* ------------------- */

    // Additional
    int get_n_bit(uint32_t n);
    void set_n_bit(uint32_t n);

    // Global constants for class
    static const char hex_char[];
    static const uint16_t BASIC_ARRAY_SIZE;
};

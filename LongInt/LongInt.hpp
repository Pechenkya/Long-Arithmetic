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
    // LongInt square() const;
    // LongInt power(const LongInt& pow, uint16_t res_mem_blocks) const;

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

    // Utility functions
    void set_sign(int _s);
    void resize(uint16_t new_arr_size); 
    void shrink_to_fit();
    uint64_t* get_memory();
    uint16_t get_arr_size() const;
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

    // Global constants for class
    static const char hex_char[];
    static const uint16_t BASIC_ARRAY_SIZE;
};
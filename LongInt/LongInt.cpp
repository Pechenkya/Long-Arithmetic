#include "LongInt.hpp"
#include <algorithm>

#include <iostream>

// Memory alignment constants
#define MEMORY_BLOCK_SIZE 64
#define MSB_SHIFT 63

// 4-bit mask for hex translation
#define HEX_MASK 15

// Shift logic
#define REST 63
#define GLOBAL_SHIFT_DIVISION 6

// static array used to convert integer value to hex_char
const char LongInt::hex_char[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const uint16_t LongInt::BASIC_ARRAY_SIZE = 2;

// Default constructors
LongInt::LongInt() : arr_size{BASIC_ARRAY_SIZE}, sign{0}
{
    // Allocate memory and set all bits to 0
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = 0;
    }
}

LongInt::LongInt(int64_t _default_num, uint16_t _mem_blocks) : arr_size{_mem_blocks}
{
    // Allocate memory and set all bits to 0, except last value
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size - 1; ++i)
    {
        data[i] = 0;
    }
    // Set last data to _default_num
    if(_default_num > 0)
    {
        data[arr_size - 1] = _default_num;
        sign = 1;
    }
    else if(_default_num < 0)
    {
        data[arr_size - 1] = -_default_num;
        sign = -1;
    }
    else
    {
        data[arr_size - 1] = 0;
        sign = 0;
    }
}

// Copy constructor
LongInt::LongInt(const LongInt & cp) : arr_size{cp.arr_size}, sign{cp.sign}
{
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = cp.data[i];
    }
}

// Move constructor
LongInt::LongInt(LongInt && mv) : arr_size{mv.arr_size}, sign{mv.sign}
{
    data = mv.data;
    mv.data = nullptr;
}

// Destructor
LongInt::~LongInt()
{
    if(data)
        delete[] data;
}

// Assignment operators
LongInt& LongInt::operator=(const LongInt & cp)
{
    if(data)
        delete[] data;

    sign = cp.sign;
    arr_size = cp.arr_size;
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = cp.data[i];
    }

    return *this;
}

LongInt& LongInt::operator=(LongInt && mv)
{
    if(data)
        delete[] data;

    sign = mv.sign;
    arr_size = mv.arr_size;
    data = mv.data;
    mv.data = nullptr;

    return *this;
}

LongInt& LongInt::operator=(int64_t _default_num)
{
    // We won't clean up data, we'll just rewrite the array

    // Allocate memory and set all bits to 0, except last value
    for(int i = 0; i < arr_size - 1; ++i)
    {
        data[i] = 0;
    }
    // Set last data to _default_num
    if(_default_num > 0)
    {
        data[arr_size - 1] = _default_num;
        sign = 1;
    }
    else if(_default_num < 0)
    {
        data[arr_size - 1] = -_default_num;
        sign = -1;
    }
    else
    {
        data[arr_size - 1] = 0;
        sign = 0;
    }

    return *this;
}

LongInt& LongInt::operator=(const std::string& hex_str)
{
    // Check string for correctness
    if(!(hex_str.length() > 2 && hex_str[0] == '0' && hex_str[1] == 'x' && 
        std::all_of(hex_str.begin() + 2, hex_str.end(), [](char c) -> bool {
            return (std::isalpha(c) && std::tolower(c) < 'g') || isdigit(c);
    }))) 
        return *this;   // Cannot construct
    //

    this->sign = 1;
    // Resize if needed
    if(arr_size < ((hex_str.length() - 2) >> 4) + 1)
    {
        arr_size = ((hex_str.length() - 2) >> 4) + 1;
        delete[] data;
        data = new uint64_t[arr_size];
    }

    // Clear data
    for(uint16_t i = 0; i < arr_size; ++i)
        data[i] = 0;

    // Reading loop
    for(size_t i = 2; i < hex_str.length(); ++i)
    {
        // Shift previous data
        l_shift_to(*this, 4, 0);

        // // Calculate add value to last node
        if(isdigit(hex_str[i]))
            data[arr_size - 1] += hex_str[i] - 48;               // First num
        else
            data[arr_size - 1] += std::tolower(hex_str[i]) - 87; // First char + 10
    }

    return *this;
}

// Arithmetic operations
LongInt LongInt::operator+(const LongInt& r) const
{
    // If signs are same, just add data and set current sign
    if(this->sign == r.sign)
        return add_data(*this, r);          // In this static method we add binary data and set right sign
    else if(cmp_data_less(*this, r))
            return sub_data(r, *this);      // In this static method we substract binary data and set sign of int with greater data
    else
        return sub_data(*this, r);
}

LongInt LongInt::operator-(const LongInt& r) const
{
    // Check for zeroes
    if(r.sign == 0)
        return *this;
    
    LongInt result;
    if(this->sign == 0)
    {
        result = r;
        result.set_sign(-r.sign);
    }
    else if(this->sign != r.sign)
    {
        // Add data and set sign of this (left)
        result = add_data(*this, r);
        result.set_sign(this->sign);    // this->sign - sign of left value
    }
    else if(cmp_data_less(*this, r))
    {
        result = sub_data(r, *this);
        result.set_sign(this->sign);    // this->sign == -r.sing
    }
    else
    {
        result = sub_data(*this, r);    // sub sets sign value of left operand
        if(result.empty_upper_blocks() == result.arr_size)
            result.set_sign(0);
    }
    
    return result;
}


// Binary operations (no sign involved)
LongInt LongInt::operator<<(long long n) const
{
    // Check for safe input
    if(n <= 0)
        return *this;

    // Calculate global shift
    uint16_t glob_shift = (n >> GLOBAL_SHIFT_DIVISION);

    // Calculate local shift (not longer than memory block)
    uint16_t loc_shift = n & REST;

    LongInt result(0, this->arr_size);

    // Global + local shift (from left to right)
    l_shift_to(result, loc_shift, glob_shift);

    if(result.empty_upper_blocks() != result.arr_size)
        result.sign = this->sign;
    
    return result;  
}

LongInt LongInt::operator>>(long long n) const
{
    // Check for safe input
    if(n <= 0)
        return *this;

    // Calculate global shift
    uint16_t glob_shift = (n >> GLOBAL_SHIFT_DIVISION);

    // Calculate local shift (not longer than memory block)
    uint16_t loc_shift = n & REST;

    LongInt result(0, this->arr_size);

    // Global + local shift (from right to left)
    r_shift_to(result, loc_shift, glob_shift);

    if(result.empty_upper_blocks() != result.arr_size)
        result.sign = this->sign;

    return result; 
}

LongInt LongInt::operator^(const LongInt& r) const
{
    // Get longer number and take those size
    const LongInt* longer = this;
    const LongInt* shorter = &r;
    set_longer_and_shorter(longer, shorter);

    LongInt result(*longer);
    for(uint16_t i = longer->arr_size - shorter->arr_size, counter = 0; 
        counter < shorter->arr_size; ++counter, ++i)
    {
        result.data[i] ^= shorter->data[counter];
    }
    
    if(result.empty_upper_blocks() == result.arr_size)
        result.sign = 0;
    else
        result.sign = 1;

    return result;
}

LongInt LongInt::operator&(const LongInt& r) const
{
    // Get longer number and take those size
    const LongInt* longer = this;
    const LongInt* shorter = &r;
    set_longer_and_shorter(longer, shorter);

    LongInt result(*longer);
    for(uint16_t i = longer->arr_size - shorter->arr_size, counter = 0; 
        counter < shorter->arr_size; ++counter, ++i)
    {
        result.data[i] &= shorter->data[counter];
    }
    
    if(result.empty_upper_blocks() == result.arr_size)
        result.sign = 0;
    else
        result.sign = 1;

    return result;
}

LongInt LongInt::operator|(const LongInt& r) const
{
    // Get longer number and take those size
    const LongInt* longer = this;
    const LongInt* shorter = &r;
    set_longer_and_shorter(longer, shorter);

    LongInt result(*longer);
    for(uint16_t i = longer->arr_size - shorter->arr_size, counter = 0; 
        counter < shorter->arr_size; ++counter, ++i)
    {
        result.data[i] |= shorter->data[counter];
    }
    
    if(result.empty_upper_blocks() == result.arr_size)
        result.sign = 0;
    else
        result.sign = 1;

    return result;
}

LongInt LongInt::operator~() const
{
    LongInt result = *this;

    for(uint16_t i = 0; i < arr_size; ++i)
        result.data[i] = ~data[i];

    if(result.empty_upper_blocks() == result.arr_size)
        result.sign = 0;
    else
        result.sign = 1;

    return result;
}


// Compare operators
bool LongInt::operator==(const LongInt& r) const
{
    if(this->sign != r.sign)
        return false;

    const LongInt* longer = this;
    const LongInt* shorter = &r;
    set_longer_and_shorter(longer, shorter);

    // Check for non-empty data on prefix
    uint16_t diff = longer->arr_size - shorter->arr_size;
    for(uint16_t i = 0; i < diff; ++i)
        if(longer->data[i] != 0)
            return false;

    // Compare tails
    for(uint16_t i = diff, j = 0; i < longer->arr_size; ++i, ++j)
        if(longer->data[i] != shorter->data[j])
            return false;

    return true;
}

bool LongInt::operator!=(const LongInt& r) const
{
    return !(*this == r);
}

LongInt::operator bool() const
{
    return sign == 0;
}

bool LongInt::operator<(const LongInt& r) const
{
    // First compare signs
    if(this->sign < r.sign)
        return true;
    else if(this->sign > r.sign)
        return false;
    
    if(cmp_data_less(*this, r))
        return sign + 1;
    else if(this->sign < 0)
        return true;
    
    // Equal or greater
    return false;
}

bool LongInt::operator>(const LongInt& r) const
{
    return r < *this;
}

bool LongInt::operator<=(const LongInt& r) const
{
    return !(r < *this);
}

bool LongInt::operator>=(const LongInt& r) const
{
    return !(*this < r);
}

// User output
std::ostream& operator<<(std::ostream& out, const LongInt& num)
{
    // Check output mod for hexidecimal
    if(out.flags() & std::ios_base::hex)
        return out << num.to_hex();
    else
        return out << num.to_binary();
}

std::string LongInt::to_hex() const
{
    // Zero check
    if(!sign)
        return "0x0";

    // Create string with adjusted length
    uint16_t non_zero_block = empty_upper_blocks();
    size_t len = (size_t)(MEMORY_BLOCK_SIZE >> 2) * (arr_size - non_zero_block) - (pref_zeroes(data[non_zero_block]) >> 2) + 2;
    std::string result(len, '0');

    // Filling string from the end
    size_t str_id = len - 1;
    for(int arr_id = arr_size - 1; str_id > 1; --arr_id)
    {
        for(int block_id = 0; block_id < MEMORY_BLOCK_SIZE && str_id > 1; block_id += 4)
        {
            // Check every 4 bits
            result[str_id--] = hex_char[(data[arr_id] >> block_id) & HEX_MASK];
        }
    }

    // Setting up prefix
    result[str_id] = 'x';

    // I am proud of this line
    if(sign < 0)
        return "-" + result;      

    return result;
}

std::string LongInt::to_binary() const
{
    // Zero check
    if(!sign)
        return "0b0";

    // Create string with adjusted length
    uint16_t non_zero_block = empty_upper_blocks();
    size_t len = (size_t)MEMORY_BLOCK_SIZE * (arr_size - non_zero_block) - pref_zeroes(data[non_zero_block]) + 2;
    std::string result(len, '0');

    // Filling string from the end
    size_t str_id = len - 1;
    for(int arr_id = arr_size - 1; str_id > 1; --arr_id)
    {
        for(int block_id = 0; block_id < MEMORY_BLOCK_SIZE && str_id > 1; ++block_id, --str_id)
        {
            // Getting last bit after bit-shift
            result[str_id] = (1 & (data[arr_id] >> block_id)) ? '1' : '0';
        }
    }

    result[str_id] = 'b'; // setting prefix

    // I am extremely proud of this line
    if(sign < 0)
        return "-" + result;

    return result;
}

// Utility functions
void LongInt::resize(uint16_t new_arr_size)
{
    // Check if resize is needed
    if(new_arr_size == arr_size)
        return;

    if(!data)
    {
        *this = LongInt(0, new_arr_size);
        return;
    }

    uint64_t* new_data = new uint64_t[new_arr_size];
    if(new_arr_size < arr_size)
    {
        uint16_t diff = arr_size - new_arr_size;
        for(uint16_t n = 0, old = diff; n < new_arr_size; ++n, ++old)
            new_data[n] = data[old];
    }
    else
    {
        uint16_t diff = new_arr_size - arr_size;

        for(uint16_t i = 0; i < diff; ++i)
            new_data[i] = 0;

        for(uint16_t n = diff, old = 0; n < new_arr_size; ++n, ++old)
            new_data[n] = data[old];
    }

    delete[] data;
    data = new_data;
    arr_size = new_arr_size;
}

void LongInt::shrink_to_fit()
{
    // Check for zeroes in begin
    uint16_t diff = empty_upper_blocks();

    // Then just resize
    resize(arr_size - diff);
}

uint64_t* LongInt::get_memory() 
{
    return this->data;
}

uint16_t LongInt::get_arr_size() const
{
    return this->arr_size;
}

void LongInt::set_sign(int _s)
{
    if(_s < 0)
        this->sign = -1;
    else if(_s > 0)
        this->sign = 1;
    else
        this->sign = 0;
}

uint16_t LongInt::empty_upper_blocks() const
{
    uint16_t diff = 0;          // count of blocks to remove
    while(data[diff] == 0)
        ++diff;

    return diff;
}

bool LongInt::set_longer_and_shorter(const LongInt* & longer, const LongInt* & shorter)
{
    // Return true if swaped
    const LongInt* temp;
    if(longer->arr_size < shorter->arr_size)
    {
        temp = longer;
        longer = shorter;
        shorter = temp;
        
        return true;
    }

    return false;
}

uint16_t LongInt::pref_zeroes(uint64_t val)
{
    // Return count of zeroes in number prefix
    uint16_t count = 64;
    while(val)
    {
        --count;
        val >>= 1;
    }
    return count;
}

void LongInt::l_shift_to(LongInt& target, uint16_t loc_shift, uint16_t glob_shift) const
{
    uint16_t loc_shift_inv = MEMORY_BLOCK_SIZE - loc_shift;

    if(glob_shift < arr_size)
    {
        // In case we do it to same Int, we need to save previous value of prev node
        uint64_t prev_temp = this->data[this->arr_size - 1]; 
        uint64_t next_temp;

        target.data[this->arr_size - glob_shift - 1] = (this->data[this->arr_size - 1] << loc_shift);
        for(int old = this->arr_size - 2, n = old - glob_shift; n >= 0; --n, --old)
        {   
            next_temp = this->data[old];
            target.data[n] = (this->data[old] << loc_shift) | (prev_temp >> loc_shift_inv);
            prev_temp = next_temp;
        }
    }
}

void LongInt::r_shift_to(LongInt& target, uint16_t loc_shift, uint16_t glob_shift) const
{
    uint16_t loc_shift_inv = MEMORY_BLOCK_SIZE - loc_shift;

    if(glob_shift < arr_size)
    {
        // In case we do it to same Int, we need to save previous value of prev node
        uint64_t prev_temp = this->data[this->arr_size - 1]; // In case we do it to same Int, we need to save previous value of prev node
        uint64_t next_temp;

        target.data[glob_shift] = (this->data[0] >> loc_shift);
        for(uint16_t old = 1, n = glob_shift + 1; n < target.arr_size; ++n, ++old)
        {   
            next_temp = this->data[old];
            target.data[n] = (prev_temp << loc_shift_inv) | (this->data[old] >> loc_shift);
            prev_temp = next_temp;
        }
    }
}

LongInt LongInt::add_data(const LongInt& left, const LongInt& right)
{
    const LongInt* longer = &left;
    const LongInt* shorter = &right;
    set_longer_and_shorter(longer, shorter);

    // Set result as longer value and set it's sign
    LongInt result(*longer);

    // Carry for each step could be 0 or 1
    uint64_t carry = 0;
    int l = longer->arr_size - 1;
    for(int s = shorter->arr_size - 1; s >= 0; --s, --l)
    {
        // Do standart addition on same memory block and check for carry
        result.data[l] += shorter->data[s] + carry;

        // Carry-check boolean function
        carry = (((longer->data[l] & shorter->data[s]) | ((~result.data[l]) & (longer->data[l] | shorter->data[s]))) >> MSB_SHIFT);
    }

    while(carry && l >= 0)
    {
        result.data[l] += 1;

        // Carry exists only if value was overflown
        carry = (result.data[l] == 0);
        --l;
    }
    
    // If carry left and we have no memory blocks left -> allocate more memory
    if(carry)
    {
        result.resize(longer->arr_size + 1);
        result.data[0] = 1;
    }

    return result;
}

LongInt LongInt::sub_data(const LongInt& left, const LongInt& right)
{
    // When calling this function, we are sure that left > right by abs val
    LongInt result(left);   // Capacity of left object is enough to store result

    uint64_t borrow = 0;
    int left_hi = left.empty_upper_blocks();                   // Higher non-zero memory block of left val
    int right_hi = right.arr_size - (left.arr_size - left_hi); // Bound for substraction

    // Substraction loop
    for(int i = left.arr_size - 1, j = right.arr_size - 1; i >= left_hi; --i, --j)
    {   
        // Calculate value to substract
        uint64_t to_sub = right.data[j] + borrow;

        // Do a substraction (in case of overflow bit is going to be used)
        result.data[i] -= to_sub;

        // Check if we have borrowed a bit
        borrow = left.data[i] < to_sub;     // 1 - if value was overflown
    }

    return result;
}

bool LongInt::cmp_data_less(const LongInt& left, const LongInt& right)
{
    // Get longer number and take those size
    const LongInt* longer = &left;
    const LongInt* shorter = &right;
    bool r_is_longer = set_longer_and_shorter(longer, shorter);

    uint16_t diff = longer->arr_size - shorter->arr_size;

    // Check longer for zeroes in begin
    for(uint16_t i = 0; i < diff; ++i)
        if(longer->data[i] != 0)
            return r_is_longer;
    
    // Compare tails
    for(uint16_t l = diff, s = 0; s < right.arr_size; ++l, ++s)
        if(longer->data[l] > shorter->data[s])
            return r_is_longer;              // r_is_longer and greater by abs_val
        else if(longer->data[l] < shorter->data[s])
            return !r_is_longer;             // r_is_longer but smaller by abs_val

    // Values are equal
    return false;
}
#include "LongInt.hpp"
#include <exception>

// #include <iostream>

#define MEMORY_BLOCK_SIZE 64
#define MEMORY_BLOCK_SHIFT 63

// static array used to convert integer value to hex_char
char LongInt::hex_char[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// Default constructors
LongInt::LongInt() : arr_size{BASIC_ARRAY_SIZE}
{
    // Allocate memory and set all bits to 0
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = 0;
    }
}

LongInt::LongInt(uint64_t _default_num, uint16_t _mem_blocks) : arr_size{_mem_blocks}
{
    // Allocate memory and set all bits to 0, except last value
    data = new uint64_t[arr_size + 1];
    for(int i = 0; i < arr_size - 1; ++i)
    {
        data[i] = 0;
    }
    // Set last data to _default_num
    data[arr_size - 1] = _default_num;
}

// Copy constructor
LongInt::LongInt(const LongInt & cp) : arr_size{cp.arr_size}
{
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = cp.data[i];
    }
}

// Move constructor
LongInt::LongInt(LongInt && mv) : arr_size{mv.arr_size}
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

    arr_size = mv.arr_size;
    data = mv.data;
    mv.data = nullptr;

    return *this;
}

LongInt& LongInt::operator=(uint64_t _default_num)
{
    // We won't clean up data, we'll just rewrite the array

    // Allocate memory and set all bits to 0, except last value
    for(int i = 0; i < arr_size - 1; ++i)
    {
        data[i] = 0;
    }
    // Set last data to _default_num
    data[arr_size - 1] = _default_num;

    return *this;
}

// Arithmetic operations
LongInt LongInt::operator+(const LongInt& r) const
{
    const LongInt* longer = this;
    const LongInt* shorter = &r;
    set_longer_and_shorter(longer, shorter);

    // Set result as longer value
    LongInt result(*longer);

    // Carry for each step could be 0 or 1
    uint64_t carry = 0;
    int l = longer->arr_size - 1;
    for(int s = shorter->arr_size - 1; s >= 0; --s, --l)
    {
        // Do standart addition on same memory block and check for carry
        result.data[l] += shorter->data[s] + carry;

        // Carry-check boolean function
        carry = (((longer->data[l] & shorter->data[s]) | ((~result.data[l]) & (longer->data[l] | shorter->data[s]))) >> MEMORY_BLOCK_SHIFT);
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


// Binary operations


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
    
    return result;
}

LongInt LongInt::operator~() const
{
    LongInt result = *this;

    for(uint16_t i = 0; i < arr_size; ++i)
        result.data[i] = ~data[i];

    return result;
}


// Compare operators
bool LongInt::operator==(const LongInt& r) const
{
    if(this->arr_size != r.arr_size)
        return false;

    for(uint16_t i = 0; i < arr_size; ++i)
        if(this->data[i] != r.data[i])
            return false;

    return true;
}

bool LongInt::operator!=(const LongInt& r) const
{
    return !(*this == r);
}

LongInt::operator bool() const
{
    for(uint16_t i = 0; i < arr_size; ++i)
        if(this->data[i] != 0)
            return true;
    
    return false;
}

bool LongInt::operator<(const LongInt& r) const
{
    // Get longer number and take those size
    const LongInt* longer = this;
    const LongInt* shorter = &r;
    bool r_is_longer = set_longer_and_shorter(longer, shorter);

    uint16_t diff = longer->arr_size - shorter->arr_size;

    // Check longer for zeroes in begin
    for(uint16_t i = 0; i < diff; ++i)
        if(longer->data[i] != 0)
            return r_is_longer;
    
    // Compare tails
    for(uint16_t l = diff, s = 0; s < r.arr_size; ++l, ++s)
        if(longer->data[l] > shorter->data[s])
            return r_is_longer;
}

bool LongInt::operator>(const LongInt& r) const
{
    return r < *this;
}

bool LongInt::operator<=(const LongInt& r) const
{
    return !(r > *this);
}

bool LongInt::operator>=(const LongInt& r) const
{
    return !(*this > r);
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
    // Create string
    uint16_t emp_blocks = empty_upper_blocks();
    size_t len = (MEMORY_BLOCK_SIZE >> 2) * (arr_size - emp_blocks) + 2;
    std::string result(len, '0');

    // Filling string from the end
    size_t str_id = len - 1;

    uint64_t mask = 15; // mask for last 4 bits
    for(int arr_id = arr_size - 1; str_id > 1; --arr_id)
    {
        for(int block_id = 0; block_id < MEMORY_BLOCK_SIZE; block_id += 4)
        {
            // Check every 4 bits
            int i = ((data[arr_id] >> block_id) & mask);
            result[str_id--] = hex_char[(data[arr_id] >> block_id) & mask];
        }
    }

    // Setting up prefix
    result[str_id] = 'x';

    return result;
}

std::string LongInt::to_binary() const
{
    // Create string
    size_t len = (size_t)MEMORY_BLOCK_SIZE * (arr_size - empty_upper_blocks()) + 2;
    std::string result(len, '0');


    // Filling string from the end
    size_t str_id = len - 1;
    for(int arr_id = arr_size - 1; str_id > 1; --arr_id)
    {
        for(int block_id = 0; block_id < MEMORY_BLOCK_SIZE; ++block_id, --str_id)
        {
            // Getting last bit after bit-shift
            result[str_id] = (1 & (data[arr_id] >> block_id)) ? '1' : '0';
        }
    }

    result[str_id] = 'b'; // setting prefix

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

uint16_t LongInt::pref_zeroes(const uint64_t& val)
{
    // Return count of zeroes in number prefix
    uint16_t count = 64;
    while(val)
    {
        --count;
        val >> 1;
    }

    return count;
}
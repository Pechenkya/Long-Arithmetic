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

LongInt& LongInt::operator=(unsigned long long _default_num)
{
    if(data)
        delete[] data;
    
    arr_size = BASIC_ARRAY_SIZE;

    // Allocate memory and set all bits to 0, except last value
    data = new uint64_t[arr_size + 1];
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
    // Temporary exception for different size (need further refactoring)
    if(this->arr_size != r.arr_size)
        throw std::out_of_range("Different size long addition called");

    LongInt result;
    // Carry for each step could be 0 or 1
    uint64_t carry = 0;
    for(int i = r.arr_size - 1; i >= 0; --i)
    {
        // Do standart addition on same memory block and check for carry
        result.data[i] = this->data[i] + r.data[i] + carry;

        // Carry-check boolean function
        carry = (((this->data[i] & r.data[i]) | ((~result.data[i]) & (this->data[i] | r.data[i]))) >> MEMORY_BLOCK_SHIFT);
    }

    return result;
}


// Binary operations


LongInt LongInt::operator^(const LongInt& r) const
{
    // Get longer number and take those size
    const LongInt* longer;
    const LongInt* shorter;
    if(this->arr_size < r.arr_size)
    {
        longer = &r;
        shorter = this;
    }
    else
    {
        longer = this;
        shorter = &r;
    }

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
    const LongInt* longer;
    const LongInt* shorter;
    if(this->arr_size < r.arr_size)
    {
        longer = &r;
        shorter = this;
    }
    else
    {
        longer = this;
        shorter = &r;
    }

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
    const LongInt* longer;
    const LongInt* shorter;
    if(this->arr_size < r.arr_size)
    {
        longer = &r;
        shorter = this;
    }
    else
    {
        longer = this;
        shorter = &r;
    }

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




// User output
std::string LongInt::to_hex() const
{
    // Create string
    size_t parts = MEMORY_BLOCK_SIZE >> 2;
    size_t len = parts * arr_size + 2;
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
    size_t len = (size_t)MEMORY_BLOCK_SIZE * arr_size + 2;
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
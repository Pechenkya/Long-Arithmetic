#include "LongInt.hpp"

// Default constructors
LongInt::LongInt() : arr_size{64}
{
    // Allocate memory and set all bits to 0
    data = new uint64_t[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = 0;
    }
}

LongInt::LongInt(uint64_t _default_num) : arr_size{63}
{
    // Allocate memory and set all bits to 0, except last value
    data = new uint64_t[arr_size + 1];
    for(int i = 0; i < arr_size; ++i)
    {
        data[i] = 0;
    }
    // Set last data to _default_num
    ++arr_size;
    data[arr_size + 1] = _default_num;
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
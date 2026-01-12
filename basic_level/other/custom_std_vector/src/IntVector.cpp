#include "IntVector.hpp"
#include <iostream>

IntVector::IntVector() : _data(nullptr), _size(0), _capacity(0)
{
}

IntVector::IntVector(IntVector&& twin) noexcept : _data(twin._data), _size(twin._size), _capacity(twin._capacity)
{
    twin._data = nullptr;
    twin._size = 0;
    twin._capacity = 0;
}

IntVector::IntVector(const IntVector& twin) : _data(nullptr), _size(twin._size), _capacity(twin._capacity)
{
    if (_capacity > 0)
    {
        _data = new int[_capacity];

        for (size_t i = 0; i < _size; ++ i)
        {
            _data[i] = twin._data[i];
        }
    }
}

IntVector::~IntVector()
{
    delete[] _data;
}


IntVector& IntVector::operator=(IntVector&& twin) noexcept
{
    if (this == &twin)
    {
        return *this;
    }

    delete[] _data;

    _data = twin._data;
    _size = twin._size;
    _capacity = twin._capacity;

    twin._data = nullptr;
    twin._size = 0;
    twin._capacity = 0;

    return *this;
}

IntVector& IntVector::operator=(const IntVector& twin)
{
    if (this == &twin)
    {
        return *this;
    }

    delete[] _data;

    _size = twin._size;
    _capacity = twin._capacity;
    _data = nullptr;

    if (_capacity > 0)
    {
        _data = new int[_capacity];

        for (size_t i = 0; i < _size; ++ i)
        {
            _data[i] = twin._data[i];
        }
    }

    return *this;
}

void IntVector::PushBack(int value)
{
    if (_size >= _capacity)
    {
        size_t new_cap = (_capacity == 0) ? 1 : _capacity * 2;

        int* new_data = new int[new_cap]{};

        for (size_t i = 0; i < _size; ++ i)
        {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_cap;
    }

    _data[_size ++] = value;
}

int& IntVector::operator[](size_t index)
{
    return _data[index];
}

size_t IntVector::Size() const
{
    return _size;
}

size_t IntVector::Capacity() const
{
    return _capacity;
}
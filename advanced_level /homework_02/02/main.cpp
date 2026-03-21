#include <iostream>
#include <stdexcept>

class SArray
{
private:
    int *_data{nullptr};
    size_t _size{0};
    size_t _capacity{0};

public:
    explicit SArray(size_t capacity) : _size(0), _capacity(capacity)
    {
        if (capacity == 0)
        {
            throw std::invalid_argument("Capacity must be greater than 0");
        }

        _data = new int[_capacity];
    }

    ~SArray()
    {
        delete[] _data;
    }

    SArray(const SArray &twin) : _data(new int[twin._capacity]), _size(twin._size), _capacity(twin._capacity)
    {
        for (size_t i{}; i < _size; ++i)
        {
            _data[i] = twin._data[i];
        }
    }

    SArray &operator=(const SArray &twin)
    {
        if (this == &twin)
        {
            return *this;
        }

        SArray temp(twin);

        std::swap(_data, temp._data);
        std::swap(_size, temp._size);
        std::swap(_capacity, temp._capacity);

        return *this;
    }

    void add_element(int value)
    {
        if (_size >= _capacity)
        {
            throw std::overflow_error("Array capacity exceeded");
        }
        _data[_size++] = value;
    }

    int get_element(size_t index) const
    {
        if (index >= _size)
        {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
};

int main()
{
    try
    {
        SArray arr(5);

        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        std::cout << arr.get_element(0) << '\n';
        std::cout << arr.get_element(2) << '\n';

        SArray new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.get_element(0) << '\n';
        std::cout << arr.get_element(2) << '\n';
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    return EXIT_SUCCESS;
}
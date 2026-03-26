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

        arr.add_element(10);
        arr.add_element(20);
        arr.add_element(30);
        arr.add_element(40);
        arr.add_element(50);

        std::cout << arr.get_element(4) << '\n';
        std::cout << arr.get_element(5) << '\n';
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    return EXIT_SUCCESS;
}
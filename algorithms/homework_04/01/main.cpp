#include <iostream>
#include <cstdlib>

void print_dynamic_array(int *arr, size_t logical_size, size_t actual_size);

int main()
{
    size_t actual_size{}, logical_size{};

    std::cout << "Input the actual size of the array: ";
    std::cin >> actual_size;

    std::cout << "Input the logical size of the array: ";
    std::cin >> logical_size;

    if (logical_size > actual_size)
    {
        std::cerr << "Logical size cannot be greater than actual size.\n";
        return EXIT_FAILURE;
    }

    int *arr{new int[actual_size]};

    for (size_t i{}; i < logical_size; ++i)
    {
        std::cout << "Input element [" << i << "]: ";
        std::cin >> arr[i];
    }

    print_dynamic_array(arr, logical_size, actual_size);

    delete[] arr;
    return EXIT_SUCCESS;
}

void print_dynamic_array(int *arr, size_t logical_size, size_t actual_size)
{
    std::cout << "Dynamic array: ";

    for (size_t i{}; i < actual_size; ++i)
    {
        (i < logical_size ? std::cout << arr[i] : std::cout << "_") << " ";
    }

    std::cout << '\n';
}
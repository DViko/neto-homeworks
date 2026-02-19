#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

struct DynamicArray
{
    int *data{nullptr};
    size_t actual_size{};
    size_t logical_size{};

    void create(size_t actual_size, size_t logical_size)
    {
        this->actual_size = actual_size;
        this->logical_size = logical_size;

        data = new int[actual_size];
    }

    void clear()
    {
        actual_size = 0;
        logical_size = 0;

        delete[] data;
        data = nullptr;
    }

    void push_back(int value)
    {
        if (logical_size == actual_size)
        {
            resize(actual_size ? actual_size * 2 : 2);
        }

        data[logical_size++] = value;
    }

    void pop_back()
    {
        if (!logical_size)
        {
            return;
        }

        --logical_size;

        if (logical_size <= actual_size / 4 && actual_size > 2)
        {
            resize(actual_size / 2);
        }
    }

private:
    void resize(size_t new_capacity)
    {
        int *new_data{new int[new_capacity]};

        for (size_t i{}; i < logical_size; ++i)
        {
            new_data[i] = data[i];
        }

        delete[] data;

        data = new_data;
        actual_size = new_capacity;
    }
};

void print_dynamic_array(int *arr, size_t actual_size, size_t logical_size, const char *label);

int main()
{
    size_t actual_size{}, logical_size{};

    std::cout << "Input the actual size of the array: ";
    std::cin >> actual_size;

    std::cout << "Input the logical size of the array: ";
    std::cin >> logical_size;

    if (actual_size < logical_size)
    {
        std::cerr << "Logical size cannot be greater than actual size\n";
        return EXIT_FAILURE;
    }

    DynamicArray arr;
    arr.create(actual_size, logical_size);

    for (size_t i{}; i < arr.logical_size; ++i)
    {
        std::cout << "Input element [" << i << "] to be added to the source array: ";
        std::cin >> arr.data[i];
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    print_dynamic_array(arr.data, arr.actual_size, arr.logical_size, "Source array: ");

    std::cout << "Enter a number to add an element to the array, or '-' to remove the last element from the array. Enter 'q' to quit: \n";

    while (true)
    {
        std::string input{};

        std::getline(std::cin, input);

        if (input.empty())
        {
            std::cout << "Input cannot be empty\n";
            continue;
        }

        if (input == "q")
        {
            break;
        }
        else if (input == "-")
        {
            arr.pop_back();
        }
        else
        {
            try
            {
                arr.push_back(std::stoi(input));
            }
            catch (...)
            {
                std::cerr << "Invalid input\n";
                continue;
            }
        }

        print_dynamic_array(arr.data, arr.actual_size, arr.logical_size, "Current array: ");
    }

    print_dynamic_array(arr.data, arr.actual_size, arr.logical_size, "Goodbye! Final array: ");

    arr.clear();
    return EXIT_SUCCESS;
}

void print_dynamic_array(int *arr, size_t actual_size, size_t logical_size, const char *label)
{
    std::cout << label;

    for (size_t i{}; i < actual_size; ++i)
    {
        std::cout << (i < logical_size ? std::to_string(arr[i]) : "_") << " ";
    }

    std::cout << '\n';
}
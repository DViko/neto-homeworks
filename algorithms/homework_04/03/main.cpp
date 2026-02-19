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

    void remove_dynamic_array_head()
    {
        if (logical_size == 0)
        {
            return;
        }

        if (should_shift())
        {
            shift_left();
        }
        else
        {
            shrink_and_shift();
        }
    }

private:
    bool should_shift() const
    {
        return (logical_size - 1) > actual_size / 3;
    }

    void shift_left()
    {
        for (size_t i{1}; i < logical_size; ++i)
        {
            data[i - 1] = data[i];
        }

        --logical_size;
    }

    void shrink_and_shift()
    {
        size_t new_actual{actual_size / 3};

        if (new_actual < 1)
        {
            new_actual = 1;
        }

        size_t new_logical{logical_size - 1};

        int *new_data{new int[new_actual]};

        for (size_t i{1}; i < logical_size && i - 1 < new_actual; ++i)
        {
            new_data[i - 1] = data[i];
        }

        delete[] data;
        data = new_data;

        actual_size = new_actual;
        logical_size = new_logical;
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

    std::cout << "Input 'y' to delete the first element of the array or 'n' to quit: \n";

    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        if (input == "n")
        {
            print_dynamic_array(arr.data, arr.actual_size, arr.logical_size, "Goodbye! Final array: ");
            break;
        }
        else if (input == "y")
        {

            if (arr.logical_size == 0)
            {
                std::cout << "Array is empty. Nothing to remove\n";
                break;
            }

            arr.remove_dynamic_array_head();
            print_dynamic_array(arr.data, arr.actual_size, arr.logical_size, "Current array: ");
        }
        else
        {
            std::cout << "Unknown input\n";
        }
    }

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
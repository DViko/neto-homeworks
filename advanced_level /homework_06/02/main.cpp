#include <iostream>

int main()
{
    int size{}, capacity{ 4 }, uniq_count{};
    int* input_numbers{ nullptr }, *unique_numbers{ nullptr };

    std::cout << "[IN]: \n";
    std::cin >> size;

    input_numbers = new int[size];
    unique_numbers = new int[capacity];

    for (int i{}; i < size; ++i)
    {
        std::cin >> input_numbers[i];
    }

    for (int i{}; i < size; ++i)
    {
        int number{ input_numbers[i] };
        bool isDuplicate{ false };

        for (int j{}; j < uniq_count; ++j)
        {
            if (unique_numbers[j] == number)
            {
                isDuplicate = true; break;
            }
        }

        if (!isDuplicate)
        {
            if (uniq_count == capacity)
            {
                int new_capacity{ capacity * 2 };

                int* new_array{ new int[new_capacity] };

                for (int k{}; k < uniq_count; ++k)
                {
                    new_array[k] = unique_numbers[k];
                }

                delete[] unique_numbers;

                unique_numbers = new_array;
                capacity = new_capacity;
            }

            unique_numbers[uniq_count++] = number;
        }
    }

    for (int i{}; i < uniq_count; ++i)
    {
        for (int j{}; j + 1 < uniq_count - i; ++j)
        {
            if (unique_numbers[j] < unique_numbers[j + 1])
            {
                int temp{ unique_numbers[j] };

                unique_numbers[j] = unique_numbers[j + 1];
                unique_numbers[j + 1] = temp;
            }
        }
    }

    std::cout << "[OUT]:\n";

    for (int i{}; i < uniq_count; ++i)
    {
        std::cout << unique_numbers[i] << "\n";
    }

    delete[] input_numbers;
    delete[] unique_numbers;
}
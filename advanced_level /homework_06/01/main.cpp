#include <iostream>
#include <string>

constexpr size_t CHAR_SET_SIZE{ 256 };

struct Pair
{
    unsigned char ch{};
    int count{};
};

int main()
{
    std::string input{ "Hello world!!" };

    int freq[CHAR_SET_SIZE]{};
    Pair arr[CHAR_SET_SIZE]{};
    size_t size{};
  
    for (size_t i{}; i < input.size(); ++i)
    {
        unsigned char c_elem { static_cast<unsigned char>(input[i]) };

        freq[c_elem]++;
    }

    for (size_t i{}; i < CHAR_SET_SIZE; ++i)
    {
        if (freq[i] > 0)
        {
            arr[size++] = Pair { static_cast<unsigned char>(i), freq[i] };
        }
    }

    for (size_t i{}; i < size; ++i)
    {
        for (size_t j{}; j + 1 < size - i; ++j)
        {
            bool swap{ false };

            if (arr[j].count < arr[j + 1].count)
            {
                swap = true;
            }
            else if (arr[j].count == arr[j + 1].count && arr[j].ch > arr[j + 1].ch)
            {
                swap = true;
            }

            if (swap)
            {
                Pair temp{ arr[j] };

                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    std::cout << "[INPUT]: " << input << "\n";
    std::cout << "[OUTPUT]:\n";

    for (size_t i{}; i < size; ++i)
    {
        std::cout << static_cast<char>(arr[i].ch) << ": " << arr[i].count << '\n';
    }

    return EXIT_SUCCESS;
}
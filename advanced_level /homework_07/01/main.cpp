#include <iostream>
#include <vector>

std::vector<int> make_unique(const std::vector<int>& input)
{
    std::vector<int> unique_elemnts {};

    for (int number : input)
    {
        bool duplicate{ false };

        for (int uniq_elem : unique_elemnts)
        {
            if (uniq_elem == number)
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
        {
            unique_elemnts.push_back(number);
        }
    }

    for (size_t i{}; i < unique_elemnts.size(); ++i)
    {
        for (size_t j{ i + 1 }; j < unique_elemnts.size(); ++j)
        {
            if (unique_elemnts[i] > unique_elemnts[j])
            {
                std::swap(unique_elemnts[i], unique_elemnts[j]);
            }
        }
    }
        

    return unique_elemnts;
}

int main()
{
    std::vector<int> input{ 1, 1, 2, 5, 6, 1, 2, 4 };

    std::vector<int> result{ make_unique(input) };

    std::cout << "[IN]: ";

    for (int x : input)
    {
        std::cout << x << " ";
    }

    std::cout << "\n[OUT]: ";

    for (int x : result)
    {
        std::cout << x << " ";
    }

    std::cout << "\n";
}
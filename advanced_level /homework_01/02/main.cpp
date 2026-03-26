#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <type_traits>

std::variant<int, std::string, std::vector<int>> get_variant();

int main()
{
    std::visit(

        [](auto&& a) {

            if constexpr (std::is_same_v<std::decay_t<decltype(a)>, int>)
            {
                std::cout << a * 2 << '\n';
            }
            else if constexpr (std::is_same_v<std::decay_t<decltype(a)>, std::string>)
            {
                std::cout << a << '\n';
            }
            else
            {
                for(int x : a)
                {
                    std::cout << x << ' ';
                }
                std::cout << '\n';
            }
        },

    get_variant());
}

std::variant<int, std::string, std::vector<int>> get_variant()
{
    std::srand(std::time(nullptr));
        
    int random_variable = std::rand() % 3;

    std::variant<int, std::string, std::vector<int>> result;

    switch (random_variable)
    {
        case 0:
            result = 5;
            break;
        case 1:
            result = "string";
            break;
        case 2:
            result = std::vector<int>{ 1, 2, 3, 4, 5 };
            break;
        default:
            break;
    }
    
    return result;
}
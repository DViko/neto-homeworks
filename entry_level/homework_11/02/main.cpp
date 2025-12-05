#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <format>

const std::array<std::string, 5> fruits
{
    "apple", "pear", "orange", "raspberry"
};


int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const std::string secret { fruits[std::rand() % fruits.size()] };
    std::string guess {};

    while (true)
    {
        std::cout << "Guess the word: ";
        std::getline(std::cin, guess);

        if (guess == secret)
        {
            std::cout << "You win! The word is \""<< secret << "\"!\n";
            break;
        }
        else
        {
            std::cout << "You didn't guess, try again.\n";
        }
    }

    return EXIT_SUCCESS;
}
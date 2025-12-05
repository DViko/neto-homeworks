#include <iostream>
#include <limits>
#include "Counter.hpp"

// g++ main.cpp Counter.cpp -o exec

int  GetInt();
bool HandleAction(Counter& counter, char action);

int main()
{
    Counter counter;
    char init_value {}, action {};

    std::cout << "Do you want to set an initial counter value? (y/n): ";
    std::cin >> init_value;

    if (init_value == 'y')
    {
        std::cout << "Enter initial value: ";
        counter.SetValue(GetInt());
    }

    do
    {
        std::cout << "Enter action ('+', '-', '=' or 'x' to exit): ";
        std::cin >> action;

    } while (HandleAction(counter, action));

    return EXIT_SUCCESS;
}

int GetInt()
{
    int value {};

    while (!(std::cin >> value))
    {
        std::cout << "Invalid input. Enter a number: ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return value;
}

bool HandleAction(Counter& counter, char action)
{
    action = std::tolower(action);

    switch (action)
    {
        case '+':
            counter.Increment();
            std::cout << "Counter value: " << counter.GetValue() << std::endl;
            return true;

        case '-':
            counter.Decrement();
            std::cout << "Counter value: " << counter.GetValue() << std::endl;
            return true;

        case '=':
            std::cout << "Current counter value: " << counter.GetValue() << std::endl;
            return true;

        case 'x':
            std::cout << "Goodbye!\n";
            return false;

        default:
            std::cout << "Invalid action. Try again.\n";
            return true;
    }
}
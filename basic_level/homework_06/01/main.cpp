#include <iostream>
#include <format>
#include "MathFunctions.hpp"

void Handler(int operation, int a, int b);

int main()
{
    int a {}, b {}, operation {};

    std::cout << "Insert nuber one: ";
    std::cin >> a;

    std::cout << "Insert number two: ";
    std::cin >> b;

    std::cout << "Choose operation (1 - addition, 2 - subtraction, 3 - multiplication, 4 - division, 5 - exponentiation): ";
    std::cin >> operation;

    Handler(operation, a, b);

    return EXIT_SUCCESS;
}

void Handler(int operation, int a, int b)
{
    switch(operation) {

        case 1: std::cout << std::format("Addition: {} + {} = {}\n", a, b, Addition(a, b));
            break;
        case 2: std::cout << std::format("Subtraction: {} - {} = {}\n", a, b, Subtraction(a, b));
            break;
        case 3: std::cout << std::format("Multiplication: {} * {} = {}\n", a, b, Multiplication(a, b));
            break;
        case 4: std::cout << std::format("Division: {} / {} = {}\n", a, b, Division(a, b));
            break;
        case 5: std::cout << std::format("Exponentiation: {} to the power of {} = {}\n", a, b, Exponentiation(a, b));
            break;
        default: std::cout << "Unknown operation\n";
    }
}
#include <iostream>
#include <limits>
#include <functional>
#include "Calculator.hpp"

void GetValidNumber(std::function<bool(double)> setter, const char* message);
void PrintResults(Calculator& calculator);
bool IsNextCalculation();

int main()
{
    Calculator calculator;

    do
    {  
        GetValidNumber(
            [&calculator](double num) { return calculator.SetNum_1(num); },
            "Enter first number: "
        );
        GetValidNumber(
            [&calculator](double num) { return calculator.SetNum_2(num); },
            "Enter second number: "
        );

        PrintResults(calculator);

    } while (IsNextCalculation());
    
    return EXIT_SUCCESS;
}

void GetValidNumber(std::function<bool(double)> setter, const char* message)
{
    double number;

    while (true)
    {
        std::cout << message;
        std::cin >> number;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error! Please enter a valid number." << std::endl;
            continue;
        }

        if (!setter(number))
        {
            std::cout << "Error: Number cannot be zero." << std::endl;
            continue;
        }

        break;
    }
}

void PrintResults(Calculator& calculator)
{
    std::cout << "\nAddition (num1 + num2): " << calculator.Add_1_2() << '\n'
                << "Multiplication (num1 * num2): " << calculator.Multiply_1_2() << '\n'
                << "Subtraction (num1 - num2): " << calculator.Subtract_1_2() << '\n'
                << "Subtraction (num2 - num1): " << calculator.Subtract_2_1() << '\n'
                << "Division (num1 / num2): " << calculator.Divide_1_2() << '\n'
                << "Division (num2 / num1): " << calculator.Divide_2_1() << "\n\n";
}

bool IsNextCalculation()
{
    char choice;

    std::cout << "Do you want to perform another calculation? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
        
    return false;
}
#include <iostream>
#include <limits>
#include <functional>
#include "Calculator.hpp"

void GetNumber(std::function<bool(double)> setter, const char* message);
void Print(Calculator& calculator);
void ClearThread();
bool IsNext();

int main()
{
    Calculator calculator;

    do
    {  
        GetNumber(
            [&calculator](double num) { return calculator.SetNum_1(num); },
            "Enter first number: "
        );
        GetNumber(
            [&calculator](double num) { return calculator.SetNum_2(num); },
            "Enter second number: "
        );

        Print(calculator);

    } while (IsNext());
    
    return EXIT_SUCCESS;
}

void GetNumber(std::function<bool(double)> setter, const char* message)
{
    double number;

    while (true)
    {
        std::cout << message;
        std::cin >> number;

        if (!std::cin)
        {
            ClearThread();
            
            std::cerr << "Input error! Please enter a valid number." << '\n';
            continue;
        }

        if (!setter(number))
        {
            ClearThread();

            std::cerr << "Error: Number cannot be zero." << '\n';
            continue;
        }

        break;
    }
}

void Print(Calculator& calculator)
{
    std::cout << "\nAddition (num1 + num2): " << calculator.Add_1_2() << '\n'
                << "Multiplication (num1 * num2): " << calculator.Multiply_1_2() << '\n'
                << "Subtraction (num1 - num2): " << calculator.Subtract_1_2() << '\n'
                << "Subtraction (num2 - num1): " << calculator.Subtract_2_1() << '\n'
                << "Division (num1 / num2): " << calculator.Divide_1_2() << '\n'
                << "Division (num2 / num1): " << calculator.Divide_2_1() << "\n\n";
}

bool IsNext()
{
    char choice {};

    std::cout << "Do you want to perform another calculation? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        ClearThread();
        return true;
    }

    return false;
}

void ClearThread()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
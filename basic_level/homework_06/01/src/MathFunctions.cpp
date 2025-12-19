#include "MathFunctions.hpp"

int Addition(int a, int b)
{
    return a + b;
}

int Subtraction(int a, int b)
{
    return a - b;
}

int Multiplication(int a, int b)
{
    return a * b;
}

int Division(int a, int b)
{
    return a / b;
}

int Exponentiation(int a, int b)
{
    int result {1};

    for (int i {}; i < b; i ++)
    {
        result *= a;
    }

    return result;
}
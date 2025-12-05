#include <iostream>

namespace Math
{
    namespace addition
    {
        int doIt(int a, int b) { return a + b; }
    }
    namespace subtraction
    {
        int doIt(int a, int b) { return a - b; }
    }
    namespace multiplication
    {
        int doIt(int a, int b) { return a * b; }
    }
    namespace division
    {
        int doIt(int a, int b) { return a / b; }
    }
}

void printLine(const std::string& operation, int value);


int main()
{
    int x {15}, y {5};

    std::cout << "x = " << x << ", y = " << y << "\n";

    printLine("Addition", Math::addition::doIt(x, y));
    printLine("Subtraction", Math::subtraction::doIt(x, y));
    printLine("Multiplication", Math::multiplication::doIt(x, y));
    printLine("Division", Math::division::doIt(x, y));

    return EXIT_SUCCESS;
}

void printLine(const std::string& operation, int value)
{
    std::cout << operation << ": " << value << std::endl;
}
#include <iostream>

void countingFunction();


int main()
{

    for (int i = 0; i < 10; i ++)
    {
        countingFunction();
    }

    return EXIT_SUCCESS;
}

void countingFunction()
{
    static short count {0};

    std::cout << "Number of calls to the countingFunction() : " << (++ count) << std::endl;
}
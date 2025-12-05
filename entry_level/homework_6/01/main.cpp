#include <iostream>
#include <format>

int     getSum(int a, int b);
int     getDiff(int a, int b);
int     getMultiplication(int a, int b);
double  getDivision(int a, int b);


int main (int argc, char ** argv) {

    int a{5}, b{10};

    std::cout << std::format("{} + {} = {}\n", a, b, getSum(a, b));
    std::cout << std::format("{} - {} = {}\n", a, b, getDiff(a, b));
    std::cout << std::format("{} * {} = {}\n", a, b, getMultiplication(a, b));
    std::cout << std::format("{} / {} = {}\n", a, b, getDivision(a, b));

    return EXIT_SUCCESS;
}

int getSum(int a, int b) {

    return a + b;
}

int getDiff(int a, int b) {

    return a - b;
}

int getMultiplication(int a, int b) {

    return a * b;
}

double getDivision(int a, int b) {
    
    return static_cast<double> (a) / b;
}
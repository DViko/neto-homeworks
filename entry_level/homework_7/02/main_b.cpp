#include <iostream>

void arithmeticSwap(int& x, int& y);


int main(int argc, char* argv[]) {

    int x{5}, y{8};

    std::cout << "x = " << x << ", y = " << y << "\n";

    arithmeticSwap(x, y);

    std::cout << "x = " << x << ", y = " << y << "\n";

    return EXIT_SUCCESS;
}

void arithmeticSwap(int& x, int& y) {

    x = x + y;
    y = x - y;
    x = x - y;
}

/*
    1. Works for signed and unsigned numeric types (short, int, long, long long, float, double, long double).
    2. Not protected against numeric overflow.
    3. float, double, long double may lose precision with large values.
*/

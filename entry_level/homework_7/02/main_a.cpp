#include <iostream>

void classicSwap(int& x, int& y);


int main(int argc, char* argv[]) {

    int x{10}, y{4};

    std::cout << "x = " << x << ", y = " << y << "\n";

    classicSwap(x, y);

    std::cout << "x = " << x << ", y = " << y << "\n";

    return EXIT_SUCCESS;
}

void classicSwap(int& x, int& y) {

    int temp = x;
    x = y;
    y = temp;
}

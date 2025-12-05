#include <iostream>

void binarySwap(int& x, int& y);


int main(int argc, char* argv[]) {

    int x {3}, y {7};
    
    std::cout << "x = " << x << ", y = " << y << "\n";

    binarySwap(x, y);

    std::cout << "x = " << x << ", y = " << y << "\n";

    return EXIT_SUCCESS;
}

void binarySwap(int& x, int& y) {

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

/*
    x3 y7           3 / 2  1    7 / 2  1
                    2 / 2  0    3 / 2  1
                    1 / 2  1    1 / 2  1
                    0 / 2  0    0 / 2  0

                    0101        0111

    x 0101 y 0111

    x 0101 ^ 0111 x 0010 (2)
    y 0010 ^ 0111 y 0101 (3)
    x 0010 ^ 0101 x 0111 (7)

    x 0111 (7) y 0101 (3)
*/

/*
    1. Works only with integers.
    2. If x and y refer to the same variable, the result will be 0.
*/
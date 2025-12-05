#include <iostream>

int main() {

    int input_value{0};
    
    std::cout << "Enter an integer value: ";
    std::cin >> input_value;

    for (short i = 1; i <= 10; i++) {
        std::cout << input_value << " * " << i << " = " << input_value * i << '\n';
    }

    return EXIT_SUCCESS;
}
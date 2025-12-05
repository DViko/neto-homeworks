#include <iostream>

int main() {

    int input_number{0};

    std::cout << "Enter an integer: ";
    std::cin >> input_number;

    std::cout << "You entered: " << input_number << std::endl;

    return EXIT_SUCCESS;
}
#include <iostream>

int main() {

    int input_num{0};
    bool is_valid{false};

    while (!is_valid) {
        std::cout << "Enter an integer: ";

        if (std::cin >> input_num) {
            std::cout << "You entered: " << input_num << std::endl;

            is_valid = true;
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    
    return EXIT_SUCCESS;
}
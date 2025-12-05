#include <iostream>

int main() {
    
    int input_value{0}, result{0};

    do {
        std::cout << "Inter an integer or 0 for exit and get result: ";
        std::cin >> input_value;

        result += input_value;

    } while (input_value != 0);

    std::cout << "Result is: " << result << std::endl;

    return EXIT_SUCCESS;
}
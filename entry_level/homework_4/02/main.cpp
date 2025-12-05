#include <iostream>


int main() {
    
    int input_value{0}, mem_number{0}, result{0};

    std::cout << "Enter an integer: ";
    std::cin >> input_value;

    mem_number = input_value;

    if (input_value < 0)
        input_value = -input_value;

    while (input_value > 0) {

        result += input_value % 10;

        input_value /= 10;
    }

    std::cout << "Sum of number is: " << result << " because digits of number: " << mem_number << std::endl;

    return EXIT_SUCCESS;
}
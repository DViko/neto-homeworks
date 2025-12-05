#include <iostream>

int main() {

    int input_value{0}, result{0};
    bool is_true{false};

    while (!is_true) {
        
        std::cout << "Inter an integer or 0 for exit and get result: ";
        std::cin >> input_value;

        if (input_value == 0)
            is_true = true;
        else
            result += input_value;
    }

    std::cout << "Result is: " << result << std::endl;

    return EXIT_SUCCESS;
}
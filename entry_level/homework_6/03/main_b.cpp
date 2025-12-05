#include <iostream>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

bool readInteger(int& value);
void getFibonacciDigits(int index, std::vector<cpp_int>& buffer);
void printResult(int size, const std::vector<cpp_int>& result);

int main() {

    int value{0};

    std::cout << "Please, do not use too large numbers. Something like 0xF4240 \n";
    std::cout << "Input a positive number greter than zero: ";

    if (!readInteger(value)) {

        return EXIT_FAILURE;
    }

    std::vector<cpp_int> buffer(value);

    getFibonacciDigits(value, buffer);

    printResult(value, buffer);

    return EXIT_SUCCESS;
}


bool readInteger(int& value) {

    if (!(std::cin >> value)) {

        std::cout << "Invalid input: not an integer.\n";

        return false;
    }
    
    if (value <= 0) {

        std::cout << "Error: The integer must be positive and greter than zero.\n";

        return false;
    }

    return true;
}

void getFibonacciDigits(int index, std::vector<cpp_int>& buffer) {

    if (index >= 1) buffer[0] = 0;
    if (index >= 2) buffer[1] = 1;

    for (int i = 2; i < index; i++) {

        buffer[i] = buffer[i - 1] + buffer[i - 2];
    }
}

void printResult(int size, const std::vector<cpp_int>& result) {

    for (int i = 0; i < size; i ++) {

        std::cout << "Index: " << i << " Fibonacci digits: " << result[i] << "\n";
    }
}
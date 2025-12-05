#include <iostream>
#include <array>

bool        readInteger(int& value);
long long   getFibonacciDigits(int index, std::array<long long, 91>& buffer);
void        printResult(int size, const std::array<long long, 91>& result);

int main() {

    int value{0};

    std::array<long long, 91> buffer{0}, result{0};
    buffer.fill(-1);

    std::cout << "Input an integer between 1 and 91: ";
    
    if (!readInteger(value)) { return EXIT_FAILURE; }

    for (int i = 0; i < value; i ++) {

        result[i] = getFibonacciDigits(i, buffer);
    }

    printResult(value, result);

    return EXIT_SUCCESS;
}

bool readInteger(int& value) {

    if (!(std::cin >> value)) {

        std::cout << "Invalid input: not an integer.\n" << std::endl;

        return false;
    }

    if (value <= 0 || value > 91) {

        std::cout << "Error: Integer must be between 1 and 91.\n";

        return false;
    }

    return true;
}

long long getFibonacciDigits(int index, std::array<long long, 91>& buffer) {

    if (index == 0) { return 0; }
    if (index == 1) { return 1; }

    if (buffer[index] != -1) { return buffer[index]; }

    buffer[index] = getFibonacciDigits(index - 1, buffer) + getFibonacciDigits(index - 2, buffer);

    return buffer[index];
}

void printResult(int size, const std::array<long long, 91>& result) {

    for (int i = 0; i < size; i ++) {

        std::cout << "Index: " << i << " Fibonacci digits: " << result[i] << "\n";
    }
}
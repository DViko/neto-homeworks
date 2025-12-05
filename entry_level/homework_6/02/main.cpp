#include <iostream>
#include <array>
#include <format>

struct Items {

    int value;
    int power;
};


int  calculatePower(int value, int power);
void printResult(int value, int power, int result);


int main (int argc, char** argv) {

    std::array<Items, 3> items {{{5,2}, {3,3}, {4,4}}};

    for (auto [value, power] : items) {

        printResult(value, power, calculatePower(value, power));
    }

    return EXIT_SUCCESS;
}


int calculatePower(int value, int power) {

    int result{1};

    for (int i = 0; i < power; i ++) {
        
        result *= value;
    }

    return result;
}

void printResult(int value, int power, int result) {

    std::cout << std::format("{} v stepeni {} = {}\n", value, power, result);
}
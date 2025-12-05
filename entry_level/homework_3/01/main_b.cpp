#include <iostream>

void getBoolValues(short i, bool &a, bool &b);
void printBoolValues(bool a, bool b, bool result);

int main() {

    bool a{false}, b{false};

    std::cout << "operator: ||" << std::endl;
    std::cout << std::boolalpha;

    for (short i = 0; i < 4; i++) {

        getBoolValues(i, a, b);
        printBoolValues(a, b, (a || b));
    }

    std::cout << std::endl;
    std::cout << "operator: &&" << std::endl;

    for (short i = 0; i < 4; i++) {

        getBoolValues(i, a, b);
        printBoolValues(a, b, (a && b));
    }
    
    return EXIT_SUCCESS;
}

void getBoolValues(short i, bool &a, bool &b) {
    
    switch (i) {
        case 0: a = true;  b = true;
            break;
        case 1: a = false; b = true;
            break;
        case 2: a = true; b = false;
            break;
        case 3: a = false; b = false;
            break;
    }
}

void printBoolValues(bool a, bool b, bool result) {
    
    std::cout << a << "\t" << b << "\t" << result << std::endl;
}
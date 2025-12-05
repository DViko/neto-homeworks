#include <iostream>

int main() {
    
    bool values[2] = {true, false};
    
    std::cout << "operator: ||" << std::endl;
    std::cout << std::boolalpha;

    for (bool a: values) {
        for (bool b : values) {
            std::cout << b << "\t" << a << "\t" << (b || a) << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "operator: &&" << std::endl;

    for (bool a : values) {
        for (bool b : values) {
            std::cout << b << "\t" << a << "\t" << (b && a) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
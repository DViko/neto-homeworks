#include <iostream>
#include <string>

int main() {
    
    std::string input_string{"def"};

    std::cout << "What is your name ? : ";
    std::cin >> input_string;

    std::cout << "Hello : " << input_string << " !" << std::endl;

    return EXIT_SUCCESS;
}
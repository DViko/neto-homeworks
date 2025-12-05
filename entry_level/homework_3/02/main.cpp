#include <iostream>

int main() {
    
    int a{0}, b{0}, c{0};

    std::cout << "Enter value 1: ";
    std::cin >> a;
    std::cout << "Enter value 2: ";
    std::cin >> b;
    std::cout << "Enter value 3: ";
    std::cin >> c;

    int max = a > b ? (a > c ? a : c) : (b > c ? b : c);
    int min = a < b ? (a < c ? a : c) : (b < c ? b : c);
    int mid = a > b ? (a > c ? (b > c ? b : c) : a) : (b > c ? (a > c ? a : c) : b);

    std::cout << "Max: " << max << " Mid: " << mid << " Min: " << min << std::endl;
    
    return EXIT_SUCCESS;
}
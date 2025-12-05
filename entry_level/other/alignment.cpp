#include <iostream>

struct Bad {
    char c;   // 1
    int i;    // 4
    double d; // 8
};

struct Good {
    double d; // 8
    int i;    // 4
    char c;   // 1
};

int main() {
    
    std::cout << "Size of Bad: " << sizeof(Bad) << "\n";   // 24 , less compact
    std::cout << "Size of Good: " << sizeof(Good) << "\n"; // 16 , more compact
}
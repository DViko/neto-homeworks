#include <iostream>
#include <cstdlib>

int main() {
    
    bool a{false}, b{false}, result{false};
    
    std::cout << "operator: ||" << std::endl;
    std::cout << std::boolalpha;
    
    a = true; b = true;

    if (a || b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;

    a = false; b = true;

    if (a || b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
    
    a = true; b = false;

    if (a || b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
     
    a = false; b = false;

    if (a || b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
    std::cout << std::endl;

    std::cout << "operator: &&" << std::endl;
    
    a = true; b = true;

    if (a && b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;

    a = false; b = true;

    if (a && b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
    
    a = true; b = false;

    if (a && b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
    
    a = false; b = false;

    if (a && b) result = true;
    else result = false;

    std::cout << a << "\t" << b << "\t" << result << std::endl;
    
    return EXIT_SUCCESS;
}
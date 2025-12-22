#include <iostream>

#define MODE 1

#ifndef MODE

    #error MODE must be defined (0 - Training, 1 - Combat)
    
#endif

#if MODE == 1

    #define ADD(a, b) ((a) + (b))

#endif

int main()
{
    #if MODE == 0

        std::cout << "Training mode" << '\n';

    #elif MODE == 1

        std::cout << "Combat mode" << '\n';

        int a{}, b{};

        std::cout << "Insert number one: ";
        std::cin >> a;

        std::cout << "Insert number two: ";
        std::cin >> b;

        std::cout << "Addition result: " << ADD(a, b) << '\n';

    #else

        std::cout << "Unknown mode" << '\n';
        
    #endif

        return EXIT_SUCCESS;
}
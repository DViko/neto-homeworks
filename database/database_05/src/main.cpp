#include "application.hpp"

#include <iostream>

int main()
{
    try
    {
        return app::Application{}.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}

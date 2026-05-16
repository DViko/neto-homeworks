#include "application.hpp"

#include <iostream>

int main()
{
    try
    {
        return app::Application{}.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << "\n";
        return EXIT_FAILURE;
    }
}

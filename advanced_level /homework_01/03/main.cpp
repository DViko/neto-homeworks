#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

int main()
{   
    const double PI = 3.1415926;

    std::vector<std::function<void(double)>> functions
    {
        [](double a) { std::cout << "sin: " << std::sin(a) << " "; },
        [](double a) { std::cout << "cos: " << std::cos(a) << " "; }
    };
    
    std::vector<double> angles
    {
        30 * PI / 180,
        60 * PI / 180,
        90 * PI / 180
    };
    
    for (auto angle : angles)
    {
        std::cout << angle << ": ";

        for (auto& function : functions) function(angle);

        std::cout << '\n';
    }
}
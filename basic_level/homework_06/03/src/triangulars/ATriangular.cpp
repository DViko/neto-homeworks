#include "triangulars/ATriangular.hpp"
#include <iostream>
#include <format>


bool ATriangular::_Check(int a, int b, int c, int A, int B, int C) const
{
    return
            (a > 0 && b > 0 && c > 0) &&
            (A > 0 && B > 0 && C > 0) &&
            (A < 180 && B < 180 && C < 180) &&
            (A + B + C == 180) && (a + b > c && a + c > b && b + c > a);
}


ATriangular::ATriangular(const std::string& name, int a, int b, int c, int A, int B, int C)
{
    if (!_Check(a, b, c, A, B, C))
    {
        throw std::invalid_argument("Incorrect triangular parameters");
    }

    _name = name;
    _edges = {a, b, c};
    _angles = {A, B, C};
}

void ATriangular::Description() const
{
    std::cout << _name << ":\n";
    std::cout << std::format("Edges: a: {}, b: {}, c: {}\n", _edges[0], _edges[1], _edges[2]);
    std::cout << std::format("Angles: A: {}, B: {}, C: {}\n\n", _angles[0], _angles[1], _angles[2]);
}
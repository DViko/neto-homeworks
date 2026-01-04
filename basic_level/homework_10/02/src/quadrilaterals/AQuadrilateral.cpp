#include "quadrilaterals/AQuadrilateral.hpp"
#include <iostream>
#include <format>


bool AQuadrilateral::_Check(int a, int b, int c, int d, int A, int B, int C, int D) const
{
    return
            (a > 0 && b > 0 && c > 0 && d > 0) &&
            (A < 180 && B < 180 && C < 180 && D < 180) &&
            (A + B + C + D == 360);
}


AQuadrilateral::AQuadrilateral(const std::string& name, int a, int b, int c, int d, int A, int B, int C, int D)
{
    if (!_Check(a, b, c, d, A, B, C, D))
    {
        throw std::invalid_argument("Incorrect quadrilateral parameters");
    }

    _name = name;
    _edges = {a, b, c, d};
    _angles = {A, B, C, D};
}

void AQuadrilateral::Description() const
{
    std::cout << std::format
    (
        "Name: {}\nEdges: a: {}, b: {}, c: {}, d: {}\nAngles: A: {}, B: {}, C: {}, D: {}\n\n",
         _name,
         _edges[0], _edges[1], _edges[2], _edges[3],
         _angles[0], _angles[1], _angles[2], _angles[3]
    );
}
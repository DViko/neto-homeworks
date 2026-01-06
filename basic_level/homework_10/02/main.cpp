#include "base/IShape.hpp"
#include "triangulars/Triangulars.hpp"
#include "quadrilaterals/Quadrilaterals.hpp"
#include <memory>
#include <iostream>

template<typename IShape>
std::unique_ptr<IShape> CreateShape();
void Print(const IShape& shape);

int main()
{
    if (auto shape { CreateShape<Triangle>() })
    {
        Print(*shape);
    }

    if (auto shape { CreateShape<RightTriangle>() })
    {
        Print(*shape);
    }

    if (auto shape { CreateShape<Square>() })
    {
        Print(*shape);
    }
    
    if (auto shape { CreateShape<Rectangle>() })
    {
        Print(*shape);
    }

    return EXIT_SUCCESS;
}

template<typename IShape>
std::unique_ptr<IShape> CreateShape()
{
    try
    {
        return std::make_unique<IShape>();
    }
    catch (const ShapeLogicException& error)
    {
        std::cerr << "[shape logic exception]: " << error.what() << "\n\n";
    }

    return std::unique_ptr<IShape>{};
}

void Print(const IShape& shape)
{
    const auto& params { shape.Params() };

    std::cout << "Name: " << params.name << "\n";

    std::cout << "Edges: ";

    for (size_t i {}; i < params.edges.size(); i ++)
    {
        std::cout << char('a' + i) << ": " << params.edges[i] << (i + 1 < params.edges.size() ? ", " : ""); 
    }

    std::cout << "\n";

    std::cout << "Angles: ";

    for (size_t i {}; i < params.angles.size(); i ++)
    {
        std::cout << char('a' + i) << ": " << params.angles[i] << (i + 1 < params.angles.size() ? ", " : ""); 
    }

    std::cout << "\n\n";
}
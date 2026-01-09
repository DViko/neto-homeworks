#include "Factory.hpp"
#include <iostream>

void PrintShape(ShapeType type);
void Print(const IShape& shape);

int main()
{
    for (auto type : { ShapeType::Triangle, ShapeType::RightTriangle,
                       ShapeType::Rectangle, ShapeType::Square })
    {
        PrintShape(type);
    }

    return EXIT_SUCCESS;
}

void PrintShape(ShapeType type)
{
    if (auto* shape { CreateShape(type) })
    {
        Print(*shape);
        DestroyShape(shape);
    }
    else
    {
        std::cerr << "Failed to create shape: " << static_cast<int>(type) << ". Check shape_errors.log\n\n";
    }
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
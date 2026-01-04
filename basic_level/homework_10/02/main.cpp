#include "base/IShape.hpp"
#include "triangulars/THeadersList.hpp"
#include "quadrilaterals/QHeadersList.hpp"
#include <array>
#include <memory>


void PrintDescription(const IShape& shape)
{
    shape.Description();
}

int main()
{

    std::array<std::unique_ptr<IShape>, 4> shapes
    {
        std::make_unique<Triangle>(),
        std::make_unique<RightTriangle>(),
        std::make_unique<Square>(),
        std::make_unique<Rectangle>()
    };

    for (const auto& shape : shapes)
    {
        PrintDescription(*shape);
    }

    return EXIT_SUCCESS;
}
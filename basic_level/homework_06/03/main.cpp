#include "triangulars/THeadersList.hpp"
#include "quadrilaterals/QHeadersList.hpp"


void PrintDescription(const IShape* shape)
{
    shape -> Description();
}

int main()
{

    IShape* shapes[]
    { 
        new Triangle(), new RightTriangle(),
        new Square(), new Rectangle()
    };

    for (auto shape : shapes)
    {
        PrintDescription(shape);
    }

    for (auto shape : shapes)
    {
        delete shape;
    }

    return EXIT_SUCCESS;

}
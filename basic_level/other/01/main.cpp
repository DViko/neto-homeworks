#include <iostream>
#include "IShape.hpp"
#include "Descriptor.hpp"
#include "Triangle.hpp"
#include "Square.hpp"

void PrintShapeDescriptor(const Descriptor& descriptor);

int main()
{
    IShape* triangle = new Triangle();
    IShape* square = new Square();

    PrintShapeDescriptor(triangle -> ShapeDescriptor());
    PrintShapeDescriptor(square -> ShapeDescriptor());
    
    delete triangle;
    delete square;
    return EXIT_SUCCESS;
}

void PrintShapeDescriptor(const Descriptor& descriptor)
{
    std::cout << "Shape: " << descriptor.name << ", Verticles: " << descriptor.verticles_count << std::endl;
}
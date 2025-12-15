#include <iostream>
#include <format>

class IShape
{
    private:

        std::string _name;
        unsigned int _verticles;

    public:

        IShape(std::string name, unsigned int value) : _name(name), _verticles(value)
        {
        }

        virtual ~IShape() = default;

        virtual void Description() const
        {
            std::cout << std::format("Name: {}, Verticles: {}\n", _name, _verticles);
        }
};

class Shape : public IShape
{
    public:

        Shape() : IShape("Shape", 0)
        {
        }
};

class Triangle : public IShape
{
    public:

        Triangle() : IShape("Triangle", 3)
        {
        }
};

class Square : public IShape
{
    public:

        Square() : IShape("Square", 4)
        {
        }
};

void PrintDescription(const IShape* shape)
{
    shape -> Description();
}


int main()
{
    
    IShape* shape = new Shape();
    IShape* triangle = new Triangle();
    IShape* square = new Square();

    PrintDescription(shape);
    PrintDescription(triangle);
    PrintDescription(square);

    delete shape;
    delete triangle;
    delete square;

    return EXIT_SUCCESS;
}
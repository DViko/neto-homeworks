#include <iostream>
#include <exception>
#include <memory>
#include <format>

class ShapeError final : public std::domain_error
{
    public:

        explicit ShapeError(const std::string& message) : std::domain_error(message)
        {
        }
};

class IShape
{
    public:

        virtual ~IShape() = default;
        virtual void Description() const = 0;
};

class ATriangle : public IShape
{
    private:

        std::string _name;
        std::array<int, 3> _edges;
        std::array<int, 3> _angles;

        bool _Check(int A, int B, int C)
        {

            return (A + B + C == 180);
        }

    protected:

        ATriangle(std::string name, int a, int b, int c, int A, int B, int C)
        {
            if (!_Check(A, B, C))
            {
                throw ShapeError
                (
                    "Shape " + name + ", cannot be created. Reason: The sum of the angles does not equal 180"
                );
            }

            _name = name;
            _edges = {a, b, c};
            _angles = {A, B, C};
        }

    public:

        void Description() const override final
        {
            std::cout << _name << ":\n";
            std::cout << std::format
            (
                "Edges: a: {}, b: {}, c: {}; Angles: A: {}, B: {}, C: {}\n\n",
                _edges[0], _edges[1], _edges[2],
                _angles[0], _angles[1], _angles[2]
            );
        }
};

class RightTriangle final : public ATriangle
{
    public:

        RightTriangle() : ATriangle("Right triangle", 3, 4, 5, 30, 50, 90)
        {
        }
};

class EquilateralTriangle final : public ATriangle
{
    public:

        EquilateralTriangle() : ATriangle("Equilateral triangle", 30, 30, 30, 60, 60, 60)
        {
        }
};

void PrintDescription(const IShape* shape)
{
    shape -> Description();
}


int main ()
{
    std::unique_ptr<IShape> shape {};

    try
    {
        PrintDescription(std::make_unique<EquilateralTriangle>().get());
    }
    catch(const ShapeError& error)
    {
        std::cerr << "[shape error]: " << error.what() << "\n\n";
    }

    try
    {
        PrintDescription(std::make_unique<RightTriangle>().get());
    }
    catch(const ShapeError& error)
    {
        std::cerr << "[shape error]: " << error.what() << "\n\n";
    }
    
    return EXIT_SUCCESS;
}
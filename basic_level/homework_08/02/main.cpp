#include <iostream>
#include <exception>
#include <array>
#include <memory>
#include <format>

class TriangularLogicError : public std::logic_error
{
    public:

        explicit TriangularLogicError(const std::string& message) : std::logic_error(message)
        {
        }
};

class TriangularDomainError final : public TriangularLogicError
{
    public:

        using TriangularLogicError::TriangularLogicError;
};

class ITriangular
{
    public:

        virtual ~ITriangular() = default;
        virtual void Description() const = 0;
};

class ATriangular : public ITriangular
{
    private:

        std::string _name;
        std::array<int, 3> _edges;
        std::array<int, 3> _angles;

    protected:

        ATriangular(std::string name, int a, int b, int c, int A, int B, int C)
        {
            if (a + b <= c || a + c <= b || b + c <= a)
            {
                throw TriangularLogicError("Edges length must be positive and greater than zero.");
            }

            _name = name;
            _edges = {a, b, c};
            _angles = {A, B, C};
        }

        const std::array<int, 3>& Angles() const
        {
            return _angles;
        }

    public:

        void Description() const override final
        {
            std::cout << std::format
            (
                "{}: Edges: a: {}, b: {}, c: {}; Angles: A: {}, B: {}, C: {}\n",
                _name,
                _edges[0], _edges[1], _edges[2],
                _angles[0], _angles[1], _angles[2]
            );
        }
};

class RightTriangle final : public ATriangular
{
    public:

        RightTriangle() : ATriangular("Right triangle", 3, 4, 5, 50, 50, 80)
        {
            auto [A, B, C] = Angles();

            if(A != 90 && B != 90 && C != 90)
            {
                throw TriangularDomainError("A right triangle must have one angle equal to 90 degrees.");
            }
        }
};

class EquilateralTriangle final : public ATriangular
{
    public:

        EquilateralTriangle() : ATriangular("Equilateral triangle", 30, 30, 30, 60, 60, 60)
        {
            auto [A, B, C] = Angles();

            if(A != 60 || B != 60 || C != 60)
            {
                throw TriangularDomainError("An equilateral triangle must have all angles equal to 60 degrees.");
            }
        }
};

class Triangle final : public ATriangular
{
    public:

        Triangle() : ATriangular("Triangle", 0, 5, 7, 50, 60, 70)
        {
            auto [A, B, C] = Angles();

            if(A + B + C != 180)
            {
                throw TriangularDomainError("The sum of the angles in a triangle must be 180 degrees.");
            }
        }
};

class SomeTriangular final : public ATriangular
{
    public:

        SomeTriangular() : ATriangular("Some triangular", 9, 5, 7, 50, 60, 70)
        {
            throw std::runtime_error("Simulated system error.");
        }
};

template<typename ITriangular>
std::unique_ptr<ITriangular> CreateTriangular()
{
    try
    {
        return std::make_unique<ITriangular>();
    }
    catch(const TriangularDomainError& error)
    {
        std::cerr << "[triangular domain error]: " << error.what() << '\n';
    }
    catch(const TriangularLogicError& error)
    {
        std::cerr << "[triangular logic error]: " << error.what() << '\n';
    }
    catch (const std::exception& error)
    {
        std::cerr << "[std error]: " << error.what() << '\n';
    }

    return std::unique_ptr<ITriangular>{};
}

void PrintDescription(const ITriangular* shape)
{
    shape -> Description();
}

int main ()
{
    if (auto shape = CreateTriangular<Triangle>())
    {
        PrintDescription(shape.get());
    }

    if (auto shape = CreateTriangular<EquilateralTriangle>())
    {
        PrintDescription(shape.get());
    }

    if (auto shape = CreateTriangular<RightTriangle>())
    {
        PrintDescription(shape.get());
    }

    if (auto shape = CreateTriangular<SomeTriangular>())
    {
        PrintDescription(shape.get());
    }

    return EXIT_SUCCESS;
}
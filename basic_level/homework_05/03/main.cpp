#include <iostream>
#include <format>

class IShape
{
    protected:

        virtual bool IsValid() const = 0;
        virtual int Edges(size_t edge) const = 0;
        virtual int Angles(size_t angle) const = 0;

    public:

        virtual ~IShape() = default;
        virtual void Description() const = 0;
};

class ITriangle : public IShape
{
    private:

        std::string _name;
        std::array<int, 3> _edges;
        std::array<int, 3> _angles;

        bool _Check(int a, int b, int c, int A, int B, int C)
        {

            return
                    (a > 0 && b > 0 && c > 0) &&
                    (A > 0 && B > 0 && C > 0) &&
                    (A < 180 && B < 180 && C < 180) &&
                    (A + B + C == 180) && (a + b > c && a + c > b && b + c > a);
        }

    protected:

        ITriangle(std::string name, int a, int b, int c, int A, int B, int C)
        {
            if (!_Check(a, b, c, A, B, C))
            {
                throw std::invalid_argument("Incorrect triangle parameters");
            }

            _name = name;
            _edges[0] = a, _edges[1] = b, _edges[2] = c;
            _angles[0] = A, _angles[1] = B, _angles[2] = C;
        }

        virtual int Edges(size_t edge) const
        {
            return _edges[edge];
        }

        virtual int Angles(size_t angle) const
        {
            return _angles[angle];
        }

    public:

        void Description() const override
        {
            std::cout << _name << ":\n";
            std::cout << (IsValid() ? "Correct\n" : "Incorrect\n");
            std::cout << "Edges count: " << _edges.size() << "\n";
            std::cout << std::format("Edges: a: {}, b: {}, c: {}\n", _edges[0], _edges[1], _edges[2]);
            std::cout << std::format("Angles: A: {}, B: {}, C: {}\n\n", _angles[0], _angles[1], _angles[2]);
        };
};

class IQuadrilateral: public IShape
{
    private:

        std::string _name;
        std::array<int, 4> _edges;
        std::array<int, 4> _angles;

        bool _Check(int a, int b, int c, int d, int A, int B, int C, int D) const
        {
            return
                    (a > 0 && b > 0 && c > 0 && d > 0) &&
                    (A < 180 && B < 180 && C < 180 && D < 180) &&
                    (A + B + C + D == 360);
        }

    protected:

        IQuadrilateral(std::string name, int a, int b, int c, int d, int A, int B, int C, int D)
        {
            if (!_Check(a, b, c, d, A, B, C, D))
            {
                throw std::invalid_argument("Incorrect quadrilateral parameters");
            }

            _name = name;
            _edges[0] = a, _edges[1] = b, _edges[2] = c, _edges[3] = d;
            _angles[0] = A, _angles[1] = B, _angles[2] = C, _angles[3] = D;
        }

        virtual int Edges(size_t edge) const
        {
            return _edges[edge];
        }

        virtual int Angles(size_t angle) const
        {
            return _angles[angle];
        }

    public:

        void Description() const override
        {
            std::cout << _name << ":\n";
            std::cout << (IsValid() ? "Correct\n" : "Incorrect\n");
            std::cout << "Edges count: " << _edges.size() << "\n";
            std::cout << std::format("Adges: a: {}, b: {}, c: {}, d: {}\n", _edges[0], _edges[1], _edges[2], _edges[3]);
            std::cout << std::format("Angles: A: {}, B: {}, C: {}, D: {}\n\n", _angles[0], _angles[1], _angles[2], _angles[3]);
        };
};

class Triangle : public ITriangle
{
    public:

        Triangle() : ITriangle("Triangle", 10, 12, 15, 50, 60, 70)
        {
        };

        bool IsValid() const override
        {
            return true;
        }
};

class RightTriangle : public ITriangle
{
    public:

        RightTriangle() : ITriangle("Right triangle", 3, 4, 5, 37, 53, 90)
        {
        };

        bool IsValid() const override
        {
            return Angles(2) == 90;
        }
};

class IsoscelesTriangle : public ITriangle
{
    public:

        IsoscelesTriangle() : ITriangle("Isosceles triangle", 10, 15, 10, 50, 40, 90)
        {
        };

        bool IsValid() const override
        {
            return Edges(0) == Edges(2) && Angles(0) == Angles(2);
        }
};

class EquilateralTriangle : public ITriangle
{
    public:

        EquilateralTriangle() : ITriangle("Equilateral triangle", 30, 30, 30, 60, 60, 60)
        {
        };

        bool IsValid() const override
        {
            return  Edges(0) == Edges(1) && Edges(1) == Edges(2) &&
                    Angles(0) == 60 && Angles(1) == 60 && Angles(2) == 60;
        }
};

class Quadrilateral : public IQuadrilateral
{
    public:

        Quadrilateral() : IQuadrilateral("Quadrilateral", 10, 15, 20, 25, 80, 100, 90, 90)
        {
        };

        bool IsValid() const override
        {
            return true;
        }
};

class Rectangle : public IQuadrilateral
{
    public:

        Rectangle() : IQuadrilateral("Rectangle", 10, 20, 10, 20, 90, 90, 90, 90)
        {
        };

        bool IsValid() const override
        {
            return  Edges(0) == Edges(2) && Edges(1) == Edges(3) &&
                    Angles(0) == 90 && Angles(1) == 90 && Angles(2) == 90 && Angles(3) == 90;
        }
};

class Square : public IQuadrilateral
{
    public:

        Square() : IQuadrilateral("Square", 20, 20, 20, 20, 90, 90, 80, 100)
        {
        };

        bool IsValid() const override
        {
            return  Edges(0) == Edges(1) && Edges(1) == Edges(2) && Edges(2) == Edges(3) &&
                    Angles(0) == 90 && Angles(1) == 90 && Angles(2) == 90 && Angles(3) == 90;
        }
};

class Parallelogram : public IQuadrilateral
{
    public:

        Parallelogram() : IQuadrilateral("Parallelogram", 20, 30, 20, 30, 60, 120, 60, 120)
        {
        };

        bool IsValid() const override
        {
            return  Edges(0) == Edges(2) && Edges(1) == Edges(3) &&
                    Angles(0) == Angles(2) && Angles(1) == Angles(3);
        }
};

class Rhombus : public IQuadrilateral
{
    public:

        Rhombus() : IQuadrilateral("Rhombus", 30, 30, 30, 30, 60, 120, 60, 120)
        {
        };

        bool IsValid() const override
        {
            return  Edges(0) == Edges(1) && Edges(1) == Edges(2) && Edges(2) == Edges(3) &&
                    Angles(0) == Angles(2) && Angles(1) == Angles(3);
        }
};

void PrintDescription(const IShape* shape)
{
    shape -> Description();
}


int main ()
{
    IShape* shapes[] { new Triangle(), new RightTriangle(), new IsoscelesTriangle(), new EquilateralTriangle(),
                       new Quadrilateral(), new Rectangle(), new Square(), new Parallelogram(), new Rhombus()
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
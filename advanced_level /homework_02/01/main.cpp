#include <iostream>
#include <cstdlib>
#include <utility>

struct point
{
private:
    double m_x{};
    double m_y{};

public:
    point(double x, double y) : m_x{x}, m_y{y}
    {
    }

    std::pair<double, double> values() const
    {
        return {m_x, m_y};
    }
};

void print_point(const point &point_object);

int main()
{
    for (int i{}; i < 5; ++i)
    {
        point my_point(static_cast<double>(i), static_cast<double>(2 * i));
        print_point(my_point);
    }

    return EXIT_SUCCESS;
}

void print_point(const point &point_object)
{
    auto [x, y]{point_object.values()};

    std::cout << "x:" << x << ", y: " << y << '\n';
}
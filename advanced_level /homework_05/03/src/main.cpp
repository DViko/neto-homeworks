#include <iostream>
#include <vector>
#include <algorithm>

struct DivBy3Counter
{
private:
    int _sum{}, _count{};

public:
    void operator()(int x)
    {
        if (x % 3 == 0)
        {
            _sum += x;
            ++_count;
        }
    }

    int get_sum() const { return _sum; }
    int get_count() const { return _count; }
};

int main()
{
    std::vector<int> input_vector{4, 1, 3, 6, 25, 3, 54, 3};

    DivBy3Counter counter{};

    std::for_each(input_vector.begin(), input_vector.end(), std::ref(counter));

    std::cout << "get_sum() = " << counter.get_sum() << '\n';
    std::cout << "get_count() = " << counter.get_count() << '\n';
}
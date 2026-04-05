#include <iostream>
#include <vector>

template <typename T>
void move_vectors(std::vector<T> &from, std::vector<T> &to)
{
    to.insert
    (
        to.end(),
        std::make_move_iterator(from.begin()),
        std::make_move_iterator(from.end())
    );

    from.clear();
}

int main()
{
    std::vector<std::string> one{"test_string1", "test_string2"};
    std::vector<std::string> two{};

    move_vectors(one, two);

    std::cout << "one size: " << one.size() << "\n";
    std::cout << "two size: " << two.size() << "\n";
}
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>

template <typename Container>
void print_container(const Container& container)
{
    for (auto elem = container.begin(); elem != container.end(); ++elem)
    {
        std::cout << *elem;

        if (std::next(elem) != container.end()) std::cout << ", ";
    }
    std::cout << "\n";
}

int main()
{
    std::set<std::string> test_set{ "one", "two", "three", "four" };
    std::cout << "set: ";
    print_container(test_set); // The order is determined by the comparator, not by the insertion order.

    std::list<std::string> test_list{ "one", "two", "three", "four" };
    std::cout << "list: ";
    print_container(test_list);

    std::vector<std::string> test_vector{ "one", "two", "three", "four" };
    std::cout << "vector: ";
    print_container(test_vector);
}
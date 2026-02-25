#include <iostream>
#include <cstdlib>

struct Context
{
    const int *source;
    size_t size;
};

void print_pyramid(const Context &context);

int main()
{
    int array_a[6]{1, 3, 6, 5, 9, 8};
    int array_b[8]{94, 67, 18, 44, 55, 12, 6, 42};
    int array_c[10]{16, 11, 9, 10, 5, 6, 8, 1, 2, 4};

    print_pyramid({array_a, 6});
    print_pyramid({array_b, 8});
    print_pyramid({array_c, 10});

    return EXIT_SUCCESS;
}

void print(const Context &context)
{
    for (size_t node_index{}; node_index < context.size; ++node_index)
    {
        int level{};
        size_t node_num{node_index + 1};

        while (node_num > 1)
        {
            node_num /= 2;
            level++;
        }

        if (node_index == 0)
        {
            std::cout << level << " root " << context.source[node_index] << '\n';
        }
        else
        {
            size_t parent{(node_index - 1) / 2};
            const char *side{(node_index % 2 == 1) ? "left" : "right"};

            std::cout << level << " " << side << "(" << context.source[parent] << ") " << context.source[node_index] << '\n';
        }
    }
}

void print_pyramid(const Context &context)
{
    std::cout << "Source array: ";

    for (const int *elem{context.source}; elem < context.source + context.size; ++elem)
    {
        std::cout << *elem << " ";
    }

    std::cout << "\nPyramid:\n";

    print(context);

    std::cout << '\n';
}
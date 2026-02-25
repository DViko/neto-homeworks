#include <iostream>
#include <string>
#include <cstdlib>

struct Pyramid
{
    const int *data{nullptr};
    size_t size{};

    size_t parent(size_t node_index) const
    {
        return (node_index - 1) / 2;
    }

    size_t left_child(size_t node_index) const
    {
        return 2 * node_index + 1;
    }

    size_t right_child(size_t node_index) const
    {
        return 2 * node_index + 2;
    }

    int value(size_t node_index) const
    {
        return data[node_index];
    }

    int level(size_t node_index) const
    {
        int result{};

        for (size_t n{node_index + 1}; n > 1; n /= 2)
        {
            ++result;
        }

        return result;
    }

    bool has_parent(size_t node_index) const
    {
        return node_index > 0;
    }

    bool has_left(size_t node_index) const
    {
        return exists(left_child(node_index));
    }

    bool has_right(size_t node_index) const
    {
        return exists(right_child(node_index));
    }

private:
    bool exists(size_t node_index) const
    {
        return node_index < size;
    }
};

void print_pyramid(const Pyramid &pyramid);
void explore(const Pyramid &pyramid);

int main()
{
    int array[6]{1, 3, 6, 5, 9, 8};

    Pyramid pyramid{array, 6};

    print_pyramid(pyramid);
    explore(pyramid);

    return EXIT_SUCCESS;
}

void print_node(const Pyramid &pyramid, size_t node_index)
{
    const int level{pyramid.level(node_index)};

    if (!pyramid.has_parent(node_index))
    {
        std::cout << level << " root " << pyramid.value(node_index);
    }
    else
    {
        size_t parent{pyramid.parent(node_index)};
        const char *side{(node_index % 2) ? "left" : "right"};

        std::cout << level << " " << side << "(" << pyramid.value(parent) << ") " << pyramid.value(node_index);
    }
}

void print_pyramid(const Pyramid &pyramid)
{
    std::cout << "Source array: ";

    for (const int *elem{pyramid.data}; elem < pyramid.data + pyramid.size; ++elem)
    {
        std::cout << *elem << " ";
    }

    std::cout << "\nPyramid:\n";

    for (size_t node_index{}; node_index < pyramid.size; ++node_index)
    {
        print_node(pyramid, node_index);
        std::cout << '\n';
    }
}

void explore(const Pyramid &pyramid)
{
    size_t node_index{};
    std::string command{};

    while (true)
    {
        std::cout << "You are at: ";
        print_node(pyramid, node_index);

        std::cout << "\nInput command: ";
        std::cin >> command;

        if (command == "exit")
        {
            break;
        }

        size_t next{node_index};
        const char *error{nullptr};

        if (command == "up")
        {
            if (!pyramid.has_parent(node_index))
            {
                error = "Error! No parent node";
            }
            else
            {
                next = pyramid.parent(node_index);
            }
        }
        else if (command == "left")
        {
            if (!pyramid.has_left(node_index))
            {
                error = "Error! No left child";
            }
            else
            {
                next = pyramid.left_child(node_index);
            }
        }
        else if (command == "right")
        {
            if (!pyramid.has_right(node_index))
            {
                error = "Error! No right child";
            }
            else
            {
                next = pyramid.right_child(node_index);
            }
        }
        else
        {
            error = "Unknown command";
        }

        if (error)
        {
            std::cout << error << '\n';
        }
        else
        {
            node_index = next;
            std::cout << "Ok\n";
        }
    }
}
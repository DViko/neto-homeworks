#include <iostream>
#include <fstream>

int main()
{
    int capacity {0};
    int* buffer { nullptr };

    std::ifstream source ("file.txt");

    if (!source.is_open())
    {
        std::cout << "Error: cannot open input file.\n";
        return EXIT_FAILURE;
    }

    source >> capacity;

    buffer = new int[capacity]();

    for (int i {}; i < capacity; i++)
    {
        source >> buffer[i];
    }

    source.close();

    for (int i { capacity - 1 }; i >= 0; i--)
    {
        std::cout << buffer[i] << (i > 0 ? ", " : "\n");
    }

    delete[] buffer;
    buffer = nullptr;

    return EXIT_SUCCESS;
}

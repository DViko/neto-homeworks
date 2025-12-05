#include <iostream>

void swap(int* x, int* y);
void print(int& x, int& y);


int main()
{
    int x {34}, y {85};

    print(x, y);
    swap(&x, &y);
    print(x, y);

    return EXIT_SUCCESS;
}

void swap(int* x, int* y)
{
    int buff {*x};

    *x = *y;
    *y = buff;
}

void print(int& x, int& y)
{
    std::cout << "x: " << x << ", y: " << y << '\n';
}

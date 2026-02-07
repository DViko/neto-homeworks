#include <iostream>
#include <vector>

long long search_fibonacci(unsigned short number);

int main()
{
    unsigned short number{};

    std::cout << "Insert number: ";
    std::cin >> number;

    if (number < 0 || number > 92)
    {
        std::cout << "Error: number must be from 0 to 92!" << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "Result: " << search_fibonacci(number) << '\n';

    return EXIT_SUCCESS;
}

void multiply_matrix(long long A[2][2], long long B[2][2])
{
    long long x = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    long long y = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    long long z = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    long long w = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    A[0][0] = x;
    A[0][1] = y;
    A[1][0] = z;
    A[1][1] = w;
}

void power_matrix(long long F[2][2], unsigned short number)
{
    if (number <= 1)
    {
        return;
    }

    long long M[2][2] = {{1, 1}, {1, 0}};

    power_matrix(F, number / 2);
    multiply_matrix(F, F);

    if (number % 2 != 0)
    {
        multiply_matrix(F, M);
    }
}

long long search_fibonacci(unsigned short number)
{
    if (number == 0)
    {
        return 0;
    }

    long long F[2][2] = {{1, 1}, {1, 0}};
    power_matrix(F, number - 1);

    return F[0][0];
}
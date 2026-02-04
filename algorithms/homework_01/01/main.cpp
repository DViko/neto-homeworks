#include <iostream>

int calc(int *arr, int size)
{
    int ans = 0;

    for (int i = 1; i < size; i++)
    {
        ans += arr[i] - arr[i - 1];
    }

    return ans;
}

int main()
{

    int arr[] = {1, 2, 4, 7, 11};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Result: " << calc(arr, size) << std::endl;

    return EXIT_SUCCESS;
}
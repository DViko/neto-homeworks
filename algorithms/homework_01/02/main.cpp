#include <iostream>

int search(const int arr[], int size, int target)
{
    int left = 0;
    int right = size;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] <= target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return size - left;
}

int main()
{
    int arr[9]{14, 16, 19, 32, 32, 32, 56, 69, 72};
    int target = 0;

    std::cout << "Enter target value: ";
    std::cin >> target;

    int count = search(arr, 9, target);
    std::cout << "Count of elements greater than target: " << count << std::endl;

    return EXIT_SUCCESS;
}
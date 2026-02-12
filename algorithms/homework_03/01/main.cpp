#include <iostream>
#include <cstdlib>

void sort_and_print(int *arr, size_t size, const char *array_name);

int main()
{
    int arr_a[10]{3, 43, 38, 29, 18, 72, 57, 61, 2, 33};
    int arr_b[15]{88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74};
    int arr_c[18]{24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62};

    sort_and_print(arr_a, 10, "array_a");
    sort_and_print(arr_b, 15, "array_b");
    sort_and_print(arr_c, 18, "array_c");

    return EXIT_SUCCESS;
}

void merge(int *arr, size_t left, size_t mid, size_t right, int *buffer)
{
    size_t left_index{left}, right_index{mid + 1}, buffer_index{0};

    while (left_index <= mid && right_index <= right)
    {
        if (arr[left_index] <= arr[right_index])
        {
            buffer[buffer_index++] = arr[left_index++];
        }
        else
        {
            buffer[buffer_index++] = arr[right_index++];
        }
    }

    while (left_index <= mid)
    {
        buffer[buffer_index++] = arr[left_index++];
    }

    while (right_index <= right)
    {
        buffer[buffer_index++] = arr[right_index++];
    }

    std::copy(buffer, buffer + buffer_index, arr + left);
}

void merge_sort_impl(int *arr, size_t left, size_t right, int *buffer)
{
    if (left >= right)
    {
        return;
    }

    size_t mid{left + (right - left) / 2};

    merge_sort_impl(arr, left, mid, buffer);
    merge_sort_impl(arr, mid + 1, right, buffer);

    if (arr[mid] <= arr[mid + 1])
    {
        return;
    }

    merge(arr, left, mid, right, buffer);
}

void merge_sort(int *arr, size_t size)
{
    if (!arr || size <= 1)
    {
        return;
    }

    int *buffer{new int[size]};

    try
    {
        merge_sort_impl(arr, 0, size - 1, buffer);
    }
    catch (...)
    {
        delete[] buffer;
        throw;
    }

    delete[] buffer;
}

void print(const int *arr, size_t size, const char *label)
{
    std::cout << label << " ";

    for (size_t i{}; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << '\n';
}

void sort_and_print(int *arr, size_t size, const char *array_name)
{
    std::cout << array_name << '\n';

    print(arr, size, "before: ");
    merge_sort(arr, size);
    print(arr, size, "after : ");
}
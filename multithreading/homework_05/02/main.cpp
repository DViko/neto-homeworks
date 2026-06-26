#include <iostream>
#include <future>
#include <iterator>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function&& func)
{
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    constexpr difference_type threshold = 2;

    const auto length = std::distance(first, last);

    if (length <= threshold)
    {
        std::for_each(first, last, func);
        return;
    }

    Iterator middle = first;
    std::advance(middle, length / 2);

    auto left_future
    {
        std::async(std::launch::async, parallel_for_each<Iterator, Function>, first, middle, std::forward<Function>(func))
    };

    auto right_future
    {
        std::async(std::launch::async, parallel_for_each<Iterator, Function>, middle, last, std::forward<Function>(func))
    };

    left_future.get();
    right_future.get();
}

int main()
{
    std::mutex mutex;

    std::vector<int> values(12, 1);

    parallel_for_each(values.begin(), values.end(), [&mutex](int& value)
    {
        {
            std::lock_guard lock(mutex);
            std::cout << std::this_thread::get_id() << '\n';
        }

        value *= 2;
    });

    for (std::size_t i = 0; i < 12; ++i)
    {
        std::cout << values[i] << ' ';
    }

    std::cout << '\n';

    exit(EXIT_SUCCESS);
}
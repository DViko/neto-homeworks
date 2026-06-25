#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <utility>

struct Task
{
    std::future<std::size_t> future;
    std::thread worker;

    Task(std::future<std::size_t>&& f, std::thread&& t) : future(std::move(f)), worker(std::move(t))
    {
    }

    ~Task()
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&&) noexcept = default;
    Task& operator=(Task&&) noexcept = default;
};

Task find_min(const std::vector<int>& data, std::size_t begin)
{
    std::promise<std::size_t> min_index_promise;

    auto future = min_index_promise.get_future();

    std::thread worker
    (
        [&data, begin](std::promise<std::size_t> p)
        {
            std::size_t min_index = begin;

            for (std::size_t i = begin + 1; i < data.size(); ++i)
            {
                if (data[i] < data[min_index])
                {
                        min_index = i;
                }
            }

            p.set_value(min_index);
        },
        std::move(min_index_promise)
    );

    return Task
    {
        std::move(future),
        std::move(worker)
    };
}

void selection_sort(std::vector<int>& data)
{
    if (data.size() < 2)
    {
        return;
    }

    for (std::size_t i = 0; i + 1 < data.size(); ++i)
    {
        Task task = find_min(data, i);

        std::size_t min_index = task.future.get();

        if (min_index != i)
        {
            std::swap(data[i], data[min_index]);
        }
    }
}

int main()
{
    std::vector<int> values{64, 25, 12, 22, 11};

    std::cout << "Before: ";

    for (const auto value : values)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    selection_sort(values);

    std::cout << "After : ";

    for (const auto value : values)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    return EXIT_SUCCESS;
}
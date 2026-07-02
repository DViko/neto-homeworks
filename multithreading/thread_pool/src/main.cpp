#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "thread_pool.hpp"

void task_a(std::mutex& cout_mutex)
{
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "[task_a] started on thread " << std::this_thread::get_id() << '\n';
    }
}

void task_b(std::mutex& cout_mutex)
{
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "[task_b] started on thread " << std::this_thread::get_id() << '\n';
    }
}

int main()
{
    std::mutex cout_mutex;
    ThreadPool pool;

    auto template_future = pool.submit([] { return 42; });

    std::cout << "[main] template submit result = " << template_future.get() << '\n';

    std::packaged_task<void()> packaged_task([] {
        std::cout << "[main] packaged_task submit executed" << '\n';
    });

    auto packaged_future = pool.submit(std::move(packaged_task));
    packaged_future.get();

    std::function<void()> function_task = [&cout_mutex] { task_a(cout_mutex); };

    auto function_future = pool.submit(function_task);
    function_future.get();

    std::cout << "\n[main] submitting tasks...\n\n";

    for (int i = 0; i < 3; ++i)
    {
        pool.submit([&cout_mutex] { task_a(cout_mutex); });
        pool.submit([&cout_mutex] { task_b(cout_mutex); });

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\n[main] waiting for destruction...\n";

    return 0;
}
#include <thread>
#include <algorithm>

#include "thread_pool.hpp"

ThreadPool::ThreadPool()
{
    const auto count = std::max(1u, std::thread::hardware_concurrency());

    for (unsigned i = 0; i < count; ++i)
    {
        workers_.emplace_back(&ThreadPool::work, this);
    }
}

void ThreadPool::work()
{
    while (true)
    {
        auto task = queue_.pop();

        if (!task)
        {
            break;
        }

        (*task)();
    }
}

ThreadPool::~ThreadPool()
{
    queue_.stop();

    for (auto& worker : workers_)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

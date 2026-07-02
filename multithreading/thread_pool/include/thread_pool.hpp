#pragma once

#include <thread>
#include <future>
#include <vector>
#include <functional>
#include <memory>

#include "safe_queue.hpp"

class ThreadPool
{
    private:

        void work();
        std::vector<std::thread> workers_;
        SafeQueue<std::function<void()>> queue_;

    public:

        ThreadPool();
        ~ThreadPool();

        template<typename F>
        auto submit(F&& func) -> std::future<decltype(func())>
        {
            using result_type = std::invoke_result_t<F>;

            auto task = std::make_shared<std::packaged_task<result_type()>>(std::forward<F>(func));
            auto future = task->get_future();

            queue_.push([task = std::move(task)]()
            {
                (*task)();
            });

            return future;
        }
};
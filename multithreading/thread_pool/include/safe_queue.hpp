#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <optional>

template<typename T>
class SafeQueue
{
    private:

        std::queue<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable condition_;

        bool stop_ = false;
        
    public:

        void push(T value)
        {
            {
                std::lock_guard<std::mutex> lock(mutex_);

                queue_.push(std::move(value));
            }

            condition_.notify_one();
        }

        std::optional<T> pop()
        {
            std::unique_lock<std::mutex> lock(mutex_);

            condition_.wait(lock, [this]
            {
                return !queue_.empty() || stop_;
            });

            if (queue_.empty())
            {
                return std::nullopt;
            }

            T value = std::move(queue_.front());

            queue_.pop();

            return value;
        }

         void stop()
        {
            {
                std::lock_guard<std::mutex> lock(mutex_);

                stop_ = true;
            }

            condition_.notify_all();
        }
};

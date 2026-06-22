#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex cout_mtx;

class Data
{
    private:
        std::mutex mtx_;
        int value_;
        
        friend void swap(Data& lhs, Data& rhs, int thread_id);

    public:
        explicit Data(int value) : value_(value)
        {
        }
};

void swap(Data& lhs, Data& rhs, int thread_id)
{
    if (&lhs == &rhs)
    {
        return;
    }

    std::scoped_lock lock(lhs.mtx_, rhs.mtx_);

    {
        std::lock_guard<std::mutex> cout_lock(cout_mtx);

        std::cout << "[thread " << thread_id << "] before: " << "A=" << lhs.value_ << " B=" << rhs.value_ << '\n';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::swap(lhs.value_, rhs.value_);

    {
        std::lock_guard<std::mutex> cout_lock(cout_mtx);

        std::cout << "[thread " << thread_id << "] after : " << "A=" << lhs.value_ << " B=" << rhs.value_ << "\n\n";
    }
}

void worker(Data& a, Data& b, int thread_id)
{
    for (int i = 0; i < 2; ++i)
    {
        swap(a, b, thread_id);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    Data a{10};
    Data b{20};

    std::vector<std::thread> threads;

    for (int i = 0; i < 3; ++i)
    {
        threads.emplace_back(worker, std::ref(a), std::ref(b), i + 1);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "all threads finished\n";

    return EXIT_SUCCESS;
}
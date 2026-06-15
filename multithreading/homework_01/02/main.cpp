#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <numeric>
#include <algorithm>

class VectorSum
{
    private:
        std::vector<int> a_;
        std::vector<int> b_;

    public:
        explicit VectorSum(std::size_t size) : a_(size, 1), b_(size, 1)
        {
        }

        void run(std::size_t threads, std::vector<int>& result)
        {
            std::vector<std::thread> workers;
            workers.reserve(threads);

            auto worker = [this, &result](std::size_t begin, std::size_t end)
            {
                for (std::size_t i = begin; i < end; ++i)
                {
                    result[i] = a_[i] + b_[i];
                }
            };

            std::size_t size = a_.size();

            for (std::size_t th = 0; th < threads; ++th)
            {
                std::size_t begin = th * size / threads;
                std::size_t end   = (th + 1) * size / threads;

                workers.emplace_back(worker, begin, end);
            }

            for (auto& th : workers)
            {
                th.join();
            }

            auto checksum = std::accumulate(result.begin(), result.end(), 0LL);
            (void)checksum;
        }
};

long long snapshot(VectorSum& calc, std::size_t threads, std::vector<int>& buffer, std::size_t snaps)
{
    using clock = std::chrono::steady_clock;

    long long total = 0;

    for (std::size_t i = 0; i < snaps; ++i)
    {
        auto start = clock::now();

        calc.run(threads, buffer);

        auto end = clock::now();

        total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    return total / snaps;
}

int main()
{
    constexpr std::size_t snaps = 5;

    std::vector<std::size_t> sizes
    {
        1000, 10000, 100000, 1000000
    };

    std::vector<std::size_t> thread_counts
    {
        2, 4, 8, 16
    };

    std::cout << "hardware threads: " << std::thread::hardware_concurrency() << "\n\n";

    std::cout << "Size\t2th\t4th\t8th\t16th\n\n";

    for (std::size_t size : sizes)
    {
        VectorSum calc(size);
        
        std::vector<int> buffer(size);

        std::vector<long long> timings;
        timings.reserve(thread_counts.size());

        std::cout << size << '\t';

        for (std::size_t t : thread_counts)
        {
            auto time = snapshot(calc, t, buffer, snaps);
            timings.push_back(time);
            
            std::cout << time / 1000.0 << "ms\t";
        }

        auto best = std::min_element(timings.begin(), timings.end());
        std::size_t index = std::distance(timings.begin(), best);

        std::cout << " <- faster: " << thread_counts[index] << '\n';
    }

    return EXIT_SUCCESS;
}
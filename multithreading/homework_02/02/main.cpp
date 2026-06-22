#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <format>

// g++ -std=c++23 -Wall -Wextra -O2 main.cpp -o exec && ./exec

namespace ansi
{
    constexpr const char* CLEAR_SCREEN = "\033[2J";
    constexpr const char* CURSOR_HOME  = "\033[H";
    constexpr const char* CLEAR_EOL    = "\033[K";

    constexpr const char* GREEN = "\033[32m";
    constexpr const char* RED   = "\033[31m";
    constexpr const char* RESET = "\033[0m";

    inline void move(int row, int col)
    {
        std::cout << "\033[" << row << ';' << col << 'H';
    }
}

struct Config
{
    int threads = 16;
    int steps = 50;
    int bar_width = 30;

    int delay_min = 10;
    int delay_max = 100;

    int error_chance = 15;

    bool extra_load = true;
};

struct ProgressBar
{
    enum class Cell
    {
        Empty, Success, Error
    };

    std::thread::id tid{};
    std::chrono::milliseconds duration{0};

    std::vector<Cell> state{};
    int errors{};

    explicit ProgressBar(int width) : state(width, Cell::Empty)
    {
    }
};

struct SharedState
{
    std::mutex mtx{};
    std::condition_variable cv{};

    std::vector<ProgressBar> bars{};

    int updates{};
    int finished_workers{};
};

struct Simulator
{
    std::mt19937 gen{};
    std::uniform_int_distribution<int> delay{};
    std::uniform_int_distribution<int> error{};

    Simulator(unsigned seed, const Config& cfg) : gen(seed), delay(cfg.delay_min, cfg.delay_max), error(1, 100)
    {
    }

    int simulate_delay()
    {
        return delay(gen);
    }

    bool simulate_error(int chance)
    {
        return error(gen) <= chance;
    }
};

void extra_load()
{
    volatile double result = 0.0;

    for (int i = 0; i < 10'000'000; ++i)
    {
        result += std::sin(i) * std::cos(i);
    }
}

int calculate_position(int step, const Config& cfg)
{
    return std::clamp((step * cfg.bar_width) / cfg.steps, 0, cfg.bar_width - 1);
}


void worker(int id, SharedState& state, const Config& cfg)
{
    Simulator sim(id + 1000, cfg);

    auto start = std::chrono::steady_clock::now();

    {
        std::lock_guard lock(state.mtx);
        state.bars[id].tid = std::this_thread::get_id();
    }

    for (int step = 1; step <= cfg.steps; ++step)
    {
        if (cfg.extra_load)
        {
            extra_load();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sim.simulate_delay()));
        }

        bool error = sim.simulate_error(cfg.error_chance);

        int pos = calculate_position(step, cfg);

        {
            std::lock_guard lock(state.mtx);

            auto& bar = state.bars[id];

            if (error)
            {
                bar.state[pos] = ProgressBar::Cell::Error;
                ++bar.errors;
            }
            else if (bar.state[pos] == ProgressBar::Cell::Empty)
            {
                bar.state[pos] = ProgressBar::Cell::Success;
            }

            ++state.updates;
        }

        state.cv.notify_one();
    }

    auto end = std::chrono::steady_clock::now();

    {
        std::lock_guard lock(state.mtx);

        auto& bar = state.bars[id];

        bar.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        ++state.finished_workers;
        ++state.updates;
    }

    state.cv.notify_one();
}

std::vector<ProgressBar> snapshot(SharedState& state)
{
    std::lock_guard lock(state.mtx);
    
    return state.bars;
}

void render(const std::vector<ProgressBar>& bars)
{
    for (std::size_t i = 0; i < bars.size(); ++i)
    {
        const auto& bar = bars[i];

        std::ostringstream oss;

        oss << "[" << (i + 1) << "] " << bar.tid << " | ";

        for (auto cell : bar.state)
        {
            switch (cell)
            {
                case ProgressBar::Cell::Success: oss << ansi::GREEN << '#' << ansi::RESET;
                    break;

                case ProgressBar::Cell::Error: oss << ansi::RED << '!' << ansi::RESET;
                    break;

                case ProgressBar::Cell::Empty: oss << '.';
                    break;
            }
        }

        oss << " | errors=" << bar.errors << " | time=" << bar.duration.count() << "ms";

        ansi::move(static_cast<int>(i) + 1, 1);

        std::cout << oss.str() << ansi::CLEAR_EOL;
    }

    std::cout.flush();
}

void print_summary(const Config& cfg, const std::vector<ProgressBar>& bars)
{
    if (bars.empty())
    {
        return;
    }

    using ms_rep = std::chrono::milliseconds::rep;

    int total_errors = 0;

    ms_rep min_time = bars.front().duration.count();
    ms_rep max_time = bars.front().duration.count();
    ms_rep sum_time = 0;

    for (const auto& bar : bars)
    {
        total_errors += bar.errors;

        ms_rep ms = bar.duration.count();

        min_time = std::min(min_time, ms);
        max_time = std::max(max_time, ms);

        sum_time += ms;
    }

    ms_rep avg_time = sum_time / static_cast<ms_rep>(bars.size());

    ansi::move(static_cast<int>(bars.size()) + 2, 1);

    std::cout << std::format
    (
        "threads={} | steps={} | total_errors={} | min={}ms | max={}ms | avg={}ms\n",
        cfg.threads, cfg.steps, total_errors, min_time, max_time, avg_time
    );
}

int main()
{
    Config cfg;

    SharedState state;

    state.bars.resize(cfg.threads, ProgressBar(cfg.bar_width));

    std::cout << ansi::CLEAR_SCREEN << ansi::CURSOR_HOME;

    std::vector<std::thread> threads;
    threads.reserve(cfg.threads);

    for (int i = 0; i < cfg.threads; ++i)
    {
        threads.emplace_back(worker, i, std::ref(state), std::cref(cfg));
    }

    std::unique_lock lock(state.mtx);

    int last_updates = 0;

    while (true)
    {
        state.cv.wait(lock, [&]
        {
            return state.updates != last_updates;
        });

        last_updates = state.updates;

        lock.unlock();

        auto bars = snapshot(state);
        render(bars);

        lock.lock();

        if (state.finished_workers == cfg.threads)
        {
            break;
        }
    }

    lock.unlock();

    for (auto& thread: threads)
    {
        thread.join();
    }

    auto bars = snapshot(state);

    print_summary(cfg, bars);

    std::cout << "done\n";

    return EXIT_SUCCESS;
}
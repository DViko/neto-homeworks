#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<int> clients{0};
std::atomic<bool> producer_done{false};

constexpr int MAX_CLIENTS = 10;

void client_thread()
{
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int current_clients = clients.fetch_add(1, std::memory_order_seq_cst) + 1;

        std::cout << "[client] +1 -> " << current_clients << '\n';
    }

    producer_done.store(true, std::memory_order_seq_cst);
}

void operator_thread()
{
    while (true)
    {
        int value = clients.load(std::memory_order_seq_cst);

        if (value == 0)
        {
            if (producer_done.load(std::memory_order_seq_cst))
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        int new_value = clients.fetch_sub(1, std::memory_order_seq_cst) - 1;

        std::cout << "[operator] -1 -> " << new_value << '\n';
    }

    std::cout << "[operator] finished\n";
}

int main()
{
    std::thread t1(client_thread);
    std::thread t2(operator_thread);

    t1.join();
    t2.join();

    std::cout << "Done. clients = " << clients << '\n';
}
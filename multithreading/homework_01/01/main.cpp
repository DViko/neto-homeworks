#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <optional>

struct Client
{
    std::size_t id {};
};

class Queue
{
    private:
        std::mutex mutex_;
        std::queue<Client> clients_;
        std::condition_variable condition_;
        bool no_more_clients_ = false;

    public:
        void add_client(const Client& client)
        {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                clients_.push(client);

                std::cout << "[queue]: client #" << client.id << " added -> [total]: " << clients_.size() << '\n';
            }

            condition_.notify_one();
        }

        void finish_production()
        {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                no_more_clients_ = true;
            }

            condition_.notify_all();
        }

        std::optional<Client> get_next_client()
        {
            std::unique_lock<std::mutex> lock(mutex_);

            condition_.wait(lock, [this]
            {
                return !clients_.empty() || no_more_clients_;
            });

            if (clients_.empty())
            {
                return std::nullopt;
            }

            auto client = clients_.front();
            clients_.pop();

            std::cout << "[queue]: client #" << client.id  << " taken -> [total]: " << clients_.size() << '\n';

            return client;
        }
};

void produce_clients(Queue& queue, std::size_t count)
{
    for (std::size_t id = 1; id <= count; ++id)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        queue.add_client(Client{id});
    }

    queue.finish_production();
}

void process_clients(Queue& queue)
{
    while (auto client = queue.get_next_client())
    {
        std::cout << "[operator]: serving client #" << client->id << '\n';

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "[operator]: completed\n";
}


int main()
{
    std::size_t client_count;

    std::cout << "client count: ";

    if (!(std::cin >> client_count) || client_count <= 0)
    {
        std::cerr << "Error: client count must be positive\n";

        return EXIT_FAILURE;
    }

    Queue queue;

    std::thread producer(produce_clients, std::ref(queue), client_count);
    std::thread consumer(process_clients, std::ref(queue));

    producer.join();
    consumer.join();

    return EXIT_SUCCESS;
}
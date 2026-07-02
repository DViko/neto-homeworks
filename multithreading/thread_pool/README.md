# 📚 Homework_06: Thread Pool

A simple **Thread Pool** implementation built on top of a **thread-safe queue**.

This project demonstrates the basic principles of concurrent task execution using modern C++ features such as threads, mutexes, condition variables, futures, and packaged tasks.

🔹 Features:

  - Generic thread-safe queue (`SafeQueue<T>`)
  - Fixed-size thread pool
  - Automatic worker creation based on CPU cores
  - Thread synchronization using `std::condition_variable`
  - Generic `submit()` accepting any callable object
  - Support for task return values via `std::future`


## 📝 Project Structure

```text
    thread_pool/
    │
    ├── include/
    │   ├── safe_queue.hpp
    │   └── thread_pool.hpp
    │
    ├── src/
    │   ├── thread_pool.cpp
    │   └── main.cpp
    │
    ├── CMakeLists.txt
    └── README.md
```

🔸 Build and Run:

  - `cmake -S . -B build`
  - `cmake --build build`
  - `./build/exec`


## 📝 How It Works

```text
            submit(task)
                │
                ▼
    SafeQueue<std::function<void()>>
                │
                ▼
        Worker Threads (N)
                │
                ▼
            Execute Task
                │
                ▼
        std::future<Result>
```

1. The client submits a callable object
2. The callable is wrapped into a `std::packaged_task`
3. The packaged task is stored inside a lambda
4. The lambda is pushed into the thread-safe queue
5. Worker threads wait for available tasks
6. A worker executes the task
7. The task result becomes available through `std::future`

🔸 Example:

```cpp
    ThreadPool pool;

    auto future = pool.submit([] {
        return 42;
    });

    std::cout << future.get() << std::endl;

    // Output: 42
```


## 📝 Key Concepts

🔹 **`SafeQueue:`** A generic thread-safe queue that synchronizes access using:

  - `std::mutex`
  - `std::condition_variable`

Worker threads block while the queue is empty and wake up when new tasks arrive.

🔹 **`ThreadPool:`** Creates a fixed number of worker threads. Each worker repeatedly:

  - waits for a task
  - removes it from the queue
  - executes it
  - waits for the next task

🔹 **`submit():`** Accepts any callable object:

  - function
  - lambda
  - functor
  - `std::function`
  - `std::packaged_task`

Internally every task is converted into a common executable form before being stored inside the queue.

🔹 **`std::future:`** Provides asynchronous access to a task result. Calling `future.get()` waits until the task has finished and returns its value.

🔹 **`std::packaged_task:`** Wraps a callable object together with its shared stateWhen executed, the result is automatically transferred to the associated `std::future`.

### 💡 Notes:

  - `SafeQueue` is reusable and independent of `ThreadPool`
  - Worker threads never busy-wait
  - `condition_variable` avoids unnecessary CPU usage
  - `std::future` synchronizes task completion
  - `ThreadPool` owns the worker threads using **RAII**

---
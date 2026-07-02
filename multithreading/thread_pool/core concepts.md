# 📓 memo: The Evolution of Callable Objects

> This document explains the core concepts used in this project and how they relate to each other.

Modern C++ provides several ways to execute code. Each abstraction solves a problem that the previous one could not.

```text
    Function
        │
        ▼
    Lambda
        │
        ▼
    std::function
        │
        ▼
    std::packaged_task
        │
        ▼
    std::future
        │
        ▼
    std::async
```

Understanding this chain makes multithreading much easier.


## 📝 Callable Objects

🔹 **Function:** a regular function is the simplest callable object.

🔸 Example:

```cpp
    void hello()
    {
        std::cout << "Hello";
    }
```

🔹 Advantages:

  - fast
  - simple
  - no dynamic allocation

🔹 Limitations

  - cannot store state
  - cannot be created at runtime

---

🔹 **Lambda:** a lambda is an anonymous function object.

🔸 Example:

```cpp
    auto hello = []()
    {
        std::cout << "Hello";
    };
```

Unlike regular functions, lambdas can capture variables.

🔸 Example:

```cpp
    int value = 42;

    auto print = [value]
    {
        std::cout << value;
    };
```

🔹 Advantages:

  - can capture state
  - created at runtime
  - very efficient


🔹 Limitations:

  - every lambda has its own unique type

---

🔹 **`std::function:`** provides a common interface for storing any callable object. It can hold:

  - functions
  - lambdas
  - functors
  - member function wrappers

🔸 Example:

```cpp
    std::function<void()> task = []()
    {
        std::cout << "Hello";
    };
```

💡 **Why is it useful ?** Without `std::function`, every callable object has a different type. `std::function` hides those differences behind **one interface**.

---

🔹 **`std::future:`** A future represents a value that will become available later.

Instead of returning the result immediately, the program receives a future and waits only when the value is actually needed.

🔸 Example:

```cpp
    std::future<int> result;
    result.get();
```

---

🔹 **`std::packaged_task:`** A packaged task combines:

  - a callable object
  - a shared state
  - a future

🔸 Example:

```cpp
    std::packaged_task<int()> task([]()
    {
        return 42;
    });

    auto future = task.get_future();

    task();

    std::cout << future.get();

    // Output: 42
```

💡 **Why is it useful ?** It automatically transfers the return value to the associated future.

---

🔹 **`std::async`:** is a higher-level abstraction.

Instead of creating a packaged task manually, the Standard Library internally creates the necessary synchronization objects.

🔸 Example:

```cpp
    auto future = std::async([]()
    {
        return 42;
    });
```


🔹 It is essentially a convenience wrapper around concepts like:

  - callable objects
  - packaged tasks
  - futures
  - execution context

## 📝 How They Work Together

🔹 The `ThreadPool` follows this pipeline:

```text
    Callable
        │
        ▼
    submit()
        │
        ▼
    std::packaged_task
        │
        ▼
    Lambda
        │
        ▼
    std::function<void()>
        │
        ▼
    SafeQueue
        │
        ▼
    Worker Thread
        │
        ▼
    Execution
        │
        ▼
    std::future
```

💡 **Why does the queue store `std::function` ?**

A queue should only know how to execute work.

🔹 It should not know:

  - what the task returns
  - whether it originated from a lambda, function, or packaged task
  - who is waiting for the result

Every task is therefore converted into a common type: `std::function<void()>`

This keeps the queue generic, reusable, and independent from the rest of the system.

## 📝 Summary

```text
    | Component          | Responsibility                        |
    | :----------------- | :------------------------------------ |
    | Function           | Executes code                         |
    | Lambda             | Stores code and state                 |
    | std::function      | Stores any callable                   |
    | std::packaged_task | Connects a callable with a future     |
    | std::future        | Retrieves the result later            |
    | ThreadPool         | Executes tasks asynchronously         |
    | SafeQueue          | Delivers tasks safely between threads |
```

---
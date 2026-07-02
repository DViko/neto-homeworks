# 📓 memo: One Task Execution

This section describes what actually happens when a single task is submitted to the thread pool.

🔹 Let's trace this specific line of code:

```cpp
    auto future = pool.submit([] {
        return 42;
    });
```

Instead of looking at abstractions separately, let's trace the full lifecycle of one task from creation to result retrieval.


## 📝 Step 1: Lambda Creation

The lambda: `[] { return 42; }` is not just a function. It is a **compiler-generated functor object**.

🔹 The compiler generates a class like this:

```cpp
    class __Lambda_001
    {
        public:

            int operator()() const
            {
                return 42;
            }
    };
```

Then an instance of this class is created. It is precisely this object that is passed to `submit()`.

💡 **The first key point:**

  - In C++, a lambda is almost always an object.


## 📝 Step 2: `submit()` receives the callable and result type deduction

Now the template starts working.

🔹 Inside `submit()`:

```cpp
    template<typename F>    // F = __Lambda_001
    auto submit(F&& func)   // submit(__Lambda_001&& func)
```

So `submit()` works with a concrete object type.

🔹 Next line:

```cpp
    using result_type = std::invoke_result_t<F>;
```

🔹 The compiler evaluates:

```text
    func() → int
```
🔹 So:

```text
    result_type = int
```


## 📝 Step 4: Creating `std::packaged_task`

This line is the most interesting.

🔹 A packaged task is created:

```cpp
    auto task = std::make_shared<std::packaged_task<result_type()>>(std::forward<F>(func));
```

Before it, only the lambda existed. After it, a new object appears.

```text
    shared_ptr
        │
        ▼
    +------------------------+
      packaged_task<int()>   
    |------------------------|
      lambda                  
      shared state            
    +------------------------+
```

🔹 At this point:

  - nothing is executed yet
  - the lambda is only stored
  - a shared state is created internally

Think of it as a bridge between execution and result storage.


## 📝 Step 5: Creating `std::future`

Now, a very important event is taking place.

🔹 Now a shared state exists:

```cpp
    auto future = task->get_future();
```

🔹 A second object appears:

```text
    future
        │
        │
        ▼
    shared state
```

In other words, there is now shared memory.

🔹 For now, it looks like this:

  - ready = false
  - value = ???
  - exception = none

There are no results yet. The future will later read from this shared state.


## 📝 Step 6: Task is converted into a generic queue item

The thread pool does not store `packaged_task` directly.

🔹 Instead, everything is converted into: `std::function<void()>`

This ensures the queue is fully generic and independent of task types.

🔹 Why ? Because the queue shouldn't even know what is:

  - `packaged_task`
  - `future`
  - `int`
  - `string`
  - `double`

🔹 The queue needs to understand only one thing:

  - "I can perform a certain task"

🔹 So the queue stores:

```text
    wrapper lambda
    ↓
    packaged_task
    ↓
    original lambda
```

Nothing more.


## 📝 Step 7: Worker thread execution

The worker thread was here the whole time: `queue.pop()`. As soon as a task appears, the condition variable signals: "Wake up". The worker receives a `std::function<void()>` by calling `(*task)()`.

🔹 A worker thread:

  - waits on the condition variable
  - wakes up when a task arrives
  - extracts `std::function<void()>`
  - executes it

🔹 Execution chain:

```text
    worker
    ↓
    std::function
    ↓
    wrapper lambda
    ↓
    packaged_task
    ↓
    original lambda
    ↓
    42
```


## 📝 Step 8: Producing the result

The original lambda returns 42, but the worker receives nothing. Why? Because the `packaged_task` captures this value and stores it in the shared state.

🔹 For now the shared state is:

  - ready = true
  - value = 42
  - exception = none


Now main calls `future.get()`, but future does not know which thread calculated the result.

🔹 It simply watches:

  - if result is not ready → it wait
  - if result is ready → it returns the value


## 📝 Final Mental Model

```text
    Lambda
    ↓
    submit()
    ↓
    packaged_task
    ↓
    shared state ←→ future
    ↓
    wrapper lambda
    ↓
    std::function<void()>
    ↓
    SafeQueue
    ↓
    worker thread
    ↓
    execution
    ↓
    shared state = result
    ↓
    future.get()
    ↓
    result
```

💡 **Key Insight:**

🔹 Each component has a single responsibility:

  - **Lambda** → defines computation
  - **`packaged_task`** → connects execution with result storage
  - **`future`** → retrieves result later
  - **SafeQueue** → safely transfers work between threads
  - **ThreadPool** worker → executes tasks

---
# 📓 memo: CRTP (Curiously Recurring Template Pattern)

## 📝 What is CRTP ?

CRTP is a C++ design pattern where a class inherits from a template instantiated with the derived class itself.

🔹 For example:

```cpp
    template<typename Derived>
    class Base
    {
        public:
            Derived& Self()
            {
                return static_cast<Derived&>(*this);
            }
    };

    class Child : public Base<Child>
    {
    };
```

Unlike virtual inheritance, CRTP provides **compile-time polymorphism**. The compiler knows the exact derived type, allowing it to optimize away virtual dispatch.


## 📝 Why use CRTP ?

🔹 Suppose a base class implements a fluent interface:

```cpp
    builder
        .AddColumn(...)
        .AddWhere(...)
        .Build();
```

If every method returns `Base&`, chaining breaks after calling a derived-class method because the static type becomes the base class.

🔹 CRTP solves this by returning the actual derived type:

```cpp
    template<typename Derived>
    class Base
    {
        protected:
            Derived& Self()
            {
                return static_cast<Derived&>(*this);
            }

        public:
            Derived& AddSomething()
            {
                // ...
                return Self();
            }
    };
```

Now every method automatically returns the correct builder type.


## 📝 How does it work ?

🔹 When a derived object is created `Child child;` the object layout is approximately:

```text
    +----------------+
    | Base<Child>    |
    +----------------+
    | Child members  |
    +----------------+
```

`Base<Child>` is a subobject inside Child. Inside the base class, `static_cast<Child&>(*this)` does not create a new object.

🔹 It simply tells the compiler:

  - > "Treat this base subobject as the complete child object."

The object remains the same. Only the static type of the reference changes.


## 📝 Why is static_cast safe ?

This cast is only safe because `Base<Child>` exists inside a real child object.

🔹 This is correct:

```cpp
    Child child;

    Base<Child>& base = child;

    Child& derived = static_cast<Child&>(base);
```

All references point to the same object.


## 📝 What should never be done ?

Never instantiate a CRTP base class directly. A declaration like `Base<Child> base;` is the wrong way. The object contains only the base part. Casting it back to сhild `base.Self();` produces **Undefined Behavior**, because no child object actually exists.

🔹 A common way to prevent this is to make the constructor protected:

```cpp
    template<typename Derived>
    class Base
    {
        protected:
            Base() = default;
    };
```

Now only derived classes can create the base subobject.

## 📝 Practical example

🔸 Without CRTP:

```cpp
    class SqlBuilder
    {
        public:
            SqlBuilder& Select(...);
    };
```

A derived builder loses its own type during method chaining.

🔸 With CRTP:

```cpp
    template<typename Derived>
    class SelectBuilderBase
    {
        public:
            Derived& Select(...)
            {
                return Self();
            }
    };

    class SimpleSelectBuilder : public SelectBuilderBase<SimpleSelectBuilder>
    {
    };

    class AdvancedSelectBuilder : public SelectBuilderBase<AdvancedSelectBuilder>
    {
        public:
            AdvancedSelectBuilder& WhereGreater(...);
            AdvancedSelectBuilder& WhereLess(...);
    };
```

Now both builders support fluent chaining while preserving their own type.

## 📝 Summary

  - CRTP provides compile-time polymorphism.
  - `Self()` changes only the reference type, never the object.
  - The object in memory never changes during `static_cast`.
  - Never instantiate the CRTP base class directly.
  - CRTP is ideal for fluent APIs, static interfaces, mixins, and policy-based design.

---
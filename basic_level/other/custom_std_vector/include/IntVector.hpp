#include <cstddef>

#define PUBLIC_API __attribute__((visibility("default")))


class PUBLIC_API IntVector final
{

    private:

        int* _data;
        size_t _size, _capacity;

    public:

        IntVector();

        IntVector(const IntVector& other);
        IntVector& operator=(const IntVector& other);

        IntVector(IntVector&& other) noexcept;
        IntVector& operator=(IntVector&& other) noexcept;

        ~IntVector();

        void PushBack(int value);
        size_t Size() const;
        size_t Capacity() const;

        int& operator[](size_t index);
        const int& operator[](size_t index) const;
};
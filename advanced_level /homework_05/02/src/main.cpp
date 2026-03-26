#include <vector>
#include <utility>
#include <iostream>

template <typename T>
class Table
{
private:
    size_t _rows{}, _cols{};
    std::vector<T> _data{};

    struct Row
    {
        T *ptr{nullptr};

        T &operator[](size_t j)
        {

            return ptr[j];
        }

        const T &operator[](size_t j) const
        {
            return ptr[j];
        }
    };

public:
    Table(size_t rows, size_t cols) : _rows(rows), _cols(cols), _data(rows * cols)
    {
    }

    Row operator[](size_t i)
    {
        return Row{_data.data() + i * _cols};
    }

    const Row operator[](size_t i) const
    {
        return Row{const_cast<T *>(_data.data()) + i * _cols};
    }

    auto Size() const
    {
        return std::pair{_rows, _cols};
    }
};

int main()
{
    Table<int> table(2, 3);

    table[0][1] = 4;
    auto [row, col] = table.Size();

    std::cout << "Table size: " << row << " x " << col << '\n';
    std::cout << "Value at [0][1]: " << table[0][1] << '\n';
}

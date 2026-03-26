#include <iostream>
#include <vector>
#include <ranges>
#include <format>

template <typename T>
concept Multipliable = requires(T value) {
    value * value;
};

template <Multipliable T>
constexpr auto square(const T &number)
{
    return number * number;
}

template <Multipliable T>
std::vector<T> square(const std::vector<T> &vector)
{
    std::vector<T> result{};

    result.reserve(vector.size());

    for (const auto &element : vector)
    {
        result.push_back(element * element);
    }

    return result;
}

template <std::ranges::input_range R>
std::string construct(const R &input, std::string_view separator)
{
    std::string output{};

    for (auto it{input.begin()}; it != input.end(); ++it)
    {
        if (it != input.begin())
        {
            output += separator;
        }

        output += std::format("{}", *it);
    }

    return output;
}

int main()
{
    int input_number{4};
    std::vector<int> input_vector{-1, 4, 8};

    std::cout << std::format("[IN]: {}\n", input_number);
    std::cout << std::format("[OUT]: {}\n", square(input_number));

    std::cout << std::format("[IN]: {}\n", construct(input_vector, ", "));
    std::cout << std::format("[OUT]: {}\n", construct(square(input_vector), ", "));
}
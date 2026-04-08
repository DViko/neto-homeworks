#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>

class BigInteger
{
    private:

        std::vector<int> _digits{};

    public:

        BigInteger() = default;

        BigInteger(const std::string& str)
        {
            _digits.reserve(str.size());

            std::transform(
                
                str.rbegin(), str.rend(),
                std::back_inserter(_digits),

                [](char c){ return std::isdigit(c) ? c - '0' : 0; }
            );
        }

        BigInteger(BigInteger&& twin) noexcept : _digits(std::move(twin._digits))
        {
        }

        BigInteger& operator=(BigInteger&& twin) noexcept
        {
            if (this != &twin)
            {
                _digits = std::move(twin._digits);
            }
            
            return *this;
        }

        BigInteger operator+(const BigInteger& twin) const
        {
            BigInteger result{};
            const size_t max_size{ std::max(_digits.size(), twin._digits.size()) };

            int carry{};

            for (size_t i{}; i < max_size || carry; ++i)
            {
                int sum{ carry };

                if (i < _digits.size())
                {
                    sum += _digits[i];
                }

                if (i < twin._digits.size())
                {
                    sum += twin._digits[i];
                }

                result._digits.push_back(sum % 10);
                carry = sum / 10;
            }

            return result;
        }

        BigInteger operator*(int num) const
        {
            BigInteger result{};

            int carry{};

            for (size_t i{}; i < _digits.size() || carry; ++i)
            {
                long long cur{ carry };

                if (i < _digits.size())
                {
                    cur += 1LL * _digits[i] * num;
                }

                result._digits.push_back(cur % 10);
                carry = cur / 10;
            }

            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const BigInteger& num)
        {
            for (auto elem{ num._digits.rbegin() }; elem != num._digits.rend(); ++elem)
            {
                os << *elem;
            }

            return os;
        }
};

int main()
{
    auto num_1{ BigInteger("114575") };
    auto num_2{ BigInteger("78524") };

    std::cout << "Value of num_1: " << num_1 << '\n';
    std::cout << "Value of num_2: " << num_2 << '\n';

    std::cout << "Sum of num_1 and num_2: " << (num_1 + num_2) << '\n';
    std::cout << "Multiple of num_1 by 3: " << (num_1 * 3) << '\n';

    num_2 = std::move(num_1);

    std::cout << "Value of num_2 after move assignment num_1 to num_2: " << num_2 << '\n';

    return EXIT_SUCCESS;
}

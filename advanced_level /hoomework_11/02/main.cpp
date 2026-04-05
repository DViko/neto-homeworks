#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInteger
{
    private:

        std::vector<int> digits{};

    public:

        BigInteger() = default;

        BigInteger(const std::string& str)
        {
            digits.reserve(str.size());
            {
                for (auto elem{ str.rbegin() }; elem != str.rend(); ++elem)
                {
                    digits.push_back(*elem - '0');
                }
            }
        }

        BigInteger operator+(const BigInteger& other) const
        {
            BigInteger result{};
            size_t max_size{ std::max(digits.size(), other.digits.size()) };
            result.digits.reserve(max_size + 1);

            int carry{};

            for (size_t i{}; i < max_size || carry; ++i)
            {
                int sum{ carry };

                if (i < digits.size())
                {
                    sum += digits[i];
                }
                
                if (i < other.digits.size())
                {
                    sum += other.digits[i];
                }

                result.digits.push_back(sum % 10);
                carry = sum / 10;
            }

            return result;
        }

        BigInteger operator*(int num) const
        {
            BigInteger result{};
            result.digits.reserve(digits.size() + 10);

            int carry{};

            for (size_t i{}; i < digits.size() || carry; ++i)
            {
                long long cur{ carry };

                if (i < digits.size())
                {
                    cur += static_cast<long long>(digits[i]) * num;
                }

                result.digits.push_back(cur % 10);
                carry = cur / 10;
            }

            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const BigInteger& num)
        {
            for (auto elem = num.digits.rbegin(); elem != num.digits.rend(); ++elem)
            {
                os << *elem;
            }

            return os;
        }
};

int main()
{
    auto number1{ BigInteger("114575") };
    auto number2{ BigInteger("78524") };

    auto sum{ number1 + number2 };
    std::cout << sum << '\n';

    auto mul{ number1 * 3 };
    std::cout << mul << '\n';

    return EXIT_SUCCESS;
}
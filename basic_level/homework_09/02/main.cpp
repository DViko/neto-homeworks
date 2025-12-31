#include <iostream>
#include <numeric>

class Fraction
{
    private:

        int numerator_;
        int denominator_;

        void ReducingFraction()
        {
            int g = std::gcd(numerator_, denominator_);
            numerator_ /= g;
            denominator_ /= g;
        }

    public:

        Fraction(int n, int d) : numerator_(n), denominator_(d)
        {
            ReducingFraction();
        }

        Fraction operator+(const Fraction& other) const
        {
            return Fraction
            (
                numerator_ * other.denominator_ + other.numerator_ * denominator_,
                denominator_ * other.denominator_
            );
        }

        Fraction operator-(const Fraction& other) const
        {
            return Fraction
            (
                numerator_ * other.denominator_ - other.numerator_ * denominator_,
                denominator_ * other.denominator_
            );
        }

        Fraction operator*(const Fraction& other) const
        {
            return Fraction
            (
                numerator_ * other.numerator_,
                denominator_ * other.denominator_
            );
        }

        Fraction operator/(const Fraction& other) const
        {
            return Fraction
            (
                numerator_ * other.denominator_,
                denominator_ * other.numerator_
            );
        }

        Fraction operator-() const
        {
            return Fraction(-numerator_, denominator_);
        }

        Fraction& operator++()
        {
            numerator_ += denominator_;
            return *this;
        }

        Fraction operator++(int)
        {
            Fraction temp = *this;
            ++(*this);
            return temp;
        }

        Fraction& operator--()
        {
            numerator_ -= denominator_;
            return *this;
        }

        Fraction operator--(int)
        {
            Fraction temp = *this;
            --(*this);
            return temp;
        }

        friend std::ostream& operator<<(std::ostream& os, const Fraction& f)
        {
            os << f.numerator_ << '/' << f.denominator_;
            return os;
        }
};

int main()
{
    int n1, d1, n2, d2;

    std::cout << "Enter the numerator of the fraction 1: ";
    std::cin >> n1;
    std::cout << "Enter the denominator of the fraction 1: ";
    std::cin >> d1;

    std::cout << "Enter the numerator of the fraction 2: ";
    std::cin >> n2;
    std::cout << "Enter the denominator of the fraction 2: ";
    std::cin >> d2;

    Fraction f1(n1, d1);
    Fraction f2(n2, d2);

    std::cout << f1 << " + " << f2 << " = " << f1 + f2 << '\n';
    std::cout << f1 << " - " << f2 << " = " << f1 - f2 << '\n';
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << '\n';
    std::cout << f1 << " / " << f2 << " = " << f1 / f2 << '\n';

    std::cout << "++" << f1 << " * " << f2 << " = " << ++f1 * f2 << '\n';
    std::cout << "Value of fraction 1 = " << f1 << '\n';

    std::cout << f1 << "-- * " << f2 << " = " << f1-- * f2 << '\n';
    std::cout << "Value of fraction 1 = " << f1 << '\n';

    return EXIT_SUCCESS;
}
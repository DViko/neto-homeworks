#include <iostream>
#include <string>
#include <array>
#include <format>


struct IntegersInWords {

    std::array<std::string, 10> units   {"", "one", "two", "three", "four", "five", 
                                            "six", "seven", "eight", "nine"
                                        };

    std::array<std::string, 10> teens   {"ten", "eleven", "twelve", "thirteen", 
                                            "fourteen", "fifteen", "sixteen", 
                                            "seventeen", "eighteen", "nineteen"
                                        };

    std::array<std::string, 10> tens    {"", "", "twenty", "thirty", "forty", "fifty", 
                                            "sixty", "seventy", "eighty", "ninety"
                                        };

    std::string minus{"minus"};
    std::string hundred{"hundred"};
    std::string zero{"zero"};
};

bool        readInteger(int& value, int min, int max);
std::string getConstructedString(int first_integer, int second_integer, const IntegersInWords& words);
std::string convertIntegerToString(int integer, const IntegersInWords& words);


int main() {

    IntegersInWords words;
    int first_integer{0}, second_integer{0};

    std::cout << "Enter an integer between -100 and 100: ";

    if (!readInteger(first_integer, -100, 100))
        return EXIT_FAILURE;

    std::cout << "Enter an integer between -100 and 100: ";

    if (!readInteger(second_integer, -100, 100))
        return EXIT_FAILURE;

    std::cout << getConstructedString(first_integer, second_integer, words) << std::endl;

    return EXIT_SUCCESS;
}


bool readInteger(int& value, int min, int max) {

    if (!(std::cin >> value)) {

        std::cerr << "Invalid input: not an integer." << std::endl;

        return false;
    }

    if (value < min || value > max) {

        std::cerr << std::format("Error: number must be between {} and {}.", min, max) << std::endl;

        return false;
    }

    return true;
}

std::string getConstructedString(int first_integer, int second_integer, const IntegersInWords& words) {

    std::string comp{

        (first_integer < second_integer)    ? " less than "
        : (first_integer > second_integer)  ? " greater than "
                                            : " equal to "
    };

    return std::format("{}{}{}", convertIntegerToString(first_integer, words), comp, convertIntegerToString(second_integer, words));
}

std::string convertIntegerToString(int integer, const IntegersInWords& words) {

    if (integer < 0)
        return std::format("{} {}", words.minus, convertIntegerToString(-integer, words));

    if (integer == 0)
        return words.zero;

    if (integer == 100)
        return std::format("{} {}", words.units[1], words.hundred);

    if (integer < 20)
        return integer < 10 ? words.units[integer] : words.teens[integer - 10];

    int tens_part = integer / 10;
    int units_part = integer % 10;

    return units_part == 0 ? words.tens[tens_part] 
                           : std::format("{} {}", words.tens[tens_part], words.units[units_part]);
}



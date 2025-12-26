#include <iostream>
#include <string>
#include <format>

struct CustomException : public std::exception
{
    std::string exeption {};

    CustomException(const std::string& string) : exeption(string) {}

    const char* what() const noexcept override
    {
        return exeption.c_str();
    }
};

int Check(const std::string& word, int length)
{
    if (static_cast<int>(word.length()) == length)
    {
        throw CustomException("You have entered a word of forbidden length. Goodbye.");
    }

    return static_cast<int>(word.length());
}

int main()
{
    int length {};

    std::cout << "Insert length to forbiddens: ";
    std::cin >> length;
    std::cin.ignore();

    while (true)
    {
        try
        {
            std::string word {};

            std::cout << "Insert word: ";
            std::getline(std::cin, word);

            std::cout << std::format("Length of: \"{}\" is equals to {}\n", word, Check(word, length));
        }
        catch (const CustomException& exception)
        {
            std::cout << exception.what() << '\n';
            break;
        }
    }

    return EXIT_SUCCESS;
}
#include "utils/console_io.hpp"

namespace utils
{
    void ConsoleIO::section_begin(std::string_view title)
    {
        write("\n---------- ", title, " ----------\n\n");
    }

    void ConsoleIO::section_end()
    {
        write("\n-------------------------------\n\n");
    }

    std::string ConsoleIO::read_line(std::string_view prompt)
    {
        write(prompt);

        std::string input;
        std::getline(std::cin, input);

        return input;
    }

    int ConsoleIO::read_int(std::string_view prompt)
    {
        while (true)
        {
            const auto input = ConsoleIO::read_line(prompt);

            try
            {
                return std::stoi(input);
            }
            catch (const std::invalid_argument&)
            {
                write("Invalid number");
            }
            catch (const std::out_of_range&)
            {
                write("Number out of range");
            }
        }
    }

    ConsoleIO::Row ConsoleIO::make_row(std::initializer_list<std::string> columns)
    {
        return Row{std::vector<std::string>(columns)};
    }

    void ConsoleIO::print_row(const Row& row)
    {
        for (const auto& item : row.columns)
        {
            write(item, '\n');
        }
    }
}
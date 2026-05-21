#include "utils/console_io.hpp"

#include <iomanip>
#include <string>

namespace utils
{
    void IO::section_begin(std::string_view title)
    {
        write_line("\n ---------- ", title, " ----------\n");

    }

    void IO::section_end()
    {
        write_line("\n -------------------------------\n");
    }

    void IO::info(std::string_view message)
    {
        write_line("\n", message, "\n");
    }

    void IO::exception(std::string_view message)
    {
        write_line("\n\n[ERROR] ", message, "\n");
    }

    std::string IO::read_line(std::string_view prompt)
    {
        std::cout << prompt;

        std::string input;
        std::getline(std::cin, input);

        return input;
    }

    int IO::read_int(std::string_view prompt)
    {
        while (true)
        {
            const auto input = IO::read_line(prompt);

            try
            {
                return std::stoi(input);
            }
            catch (const std::invalid_argument&)
            {
                IO::exception("Invalid number");
            }
        }
    }

    std::string IO::field(std::string_view name, std::string_view value)
    {
        std::ostringstream out;

        out << " " << std::left << std::setw(12) << (std::string(name) + ":") << value;

        return out.str();
    }

    void IO::print_table(std::string_view title, const std::vector<Row>& rows)
    {
        print_rows(title, rows,
            [](const Row& row)
            {
                for (const auto& column : row.columns)
                {
                    std::cout << column;
                }
            });
    }

    void IO::print_list(std::string_view title, const std::vector<Row>& rows)
    {
        print_rows(title, rows,
            [](const Row& row)
            {
                for (const auto& column : row.columns)
                {
                    write_line(column);
                }
            });
    }
}
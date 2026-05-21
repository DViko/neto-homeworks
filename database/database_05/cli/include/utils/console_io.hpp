#pragma once

#include <iostream>
#include <vector>
#include <string_view>

namespace utils
{
    class IO
    {       
        public:

            struct Row
            {
                std::vector<std::string> columns;
            };

            template<typename... Args>
            static void write_line(Args&&... args)
            {
                (std::cout << ... << args);
                std::cout << '\n';
            }

            template<typename Func>
            static void print_rows(std::string_view title, const std::vector<Row>& rows, Func&& printer)
            {
                section_begin(title);

                for (const auto& row : rows)
                {
                    printer(row);
                    std::cout << '\n';
                }

                section_end();
            }

            static void info(std::string_view message);
            static void exception(std::string_view message);

            static void section_begin(std::string_view title);
            static void section_end();

            static std::string read_line(std::string_view prompt);
            static int read_int(std::string_view prompt);

            static std::string field(std::string_view name, std::string_view value);
            static void print_table(std::string_view title, const std::vector<Row>& rows);
            static void print_list(std::string_view title, const std::vector<Row>& rows);
    };
}
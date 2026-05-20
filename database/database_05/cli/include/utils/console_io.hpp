#pragma once

#include "entity/contact_entity.hpp"

#include <iostream>
#include <iomanip>

namespace utils
{
    class ConsoleIO
    {       
        public:

            struct Row
            {
                std::vector<std::string> columns;
            };

            template<typename... Args>
            static void write(Args&&... args)
            {
                (std::cout << ... << args);
            }

            template<typename... Args>
            static void writef(Args&&... args)
            {
                ((std::cout << " " << std::setw(12) << std::left << args), ...);
                std::cout << "\n";
            }

            static void section_begin(std::string_view title);
            static void section_end();

            static std::string read_line(std::string_view prompt);
            static int read_int(std::string_view prompt);

            static ConsoleIO::Row make_row(std::initializer_list<std::string> columns);
            static void print_row(const ConsoleIO::Row& row);
    };
}
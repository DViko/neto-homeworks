#include <iostream>

#include "simple_select_builder.hpp"
#include "advanced_select_builder.hpp"

int main()
{
    SimpleSelectBuilder builder;

    builder
            .Select({"id"})
            .From("students")
            .Where({{"name", "Chloe"}});

    try
    {
        std::cout <<  builder.BuildQuery() << '\n';
    }
    catch(const std::exception& exeption)
    {
        std::cerr << exeption.what() << '\n';
        return 1;
    };
    

    builder
            .Select({"email", "phone"})
            .Where({{"age", "25"}});

    try
    {
        std::cout <<  builder.BuildQuery() << '\n';
    }
    catch(const std::exception& exeption)
    {
        std::cerr << exeption.what() << '\n';
        return 1;
    };

    builder = {};

    
    auto query_b = SimpleSelectBuilder{}
                .Select({"phone", "address"})
                .From("students")
                .Where({{"name", "Sophie"}, {"age", "20"}})
                .BuildQuery();

    std::cout << query_b << '\n';

    auto query_c = AdvancedSelectBuilder{}
                .Select({"email", "phone"})
                .From("students")
                .Where({{"name", "Glory"}})
                .WhereGreater("age", "20")
                .WhereLess("age", "30")
                .BuildQuery();

    std::cout << query_c << '\n';

    return 0;
}
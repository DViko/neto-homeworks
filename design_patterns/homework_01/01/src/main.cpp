#include <iostream>

#include "sql_select_builder.hpp"

int main()
{
    auto query_a = SqlSelectQueryBuilder{}
                .AddColumn("name")
                .AddColumn("phone")
                .AddFrom("students")
                .AddWhere("id", "42")
                .AddWhere("name", "John")
                .BuildQuery();

    std::cout << query_a << '\n';

    auto query_b = SqlSelectQueryBuilder{}
                 .AddColumns({"name", "phone"})
                 .AddFrom("students")
                 .AddWhere({{"id", "43"}, {"name", "Sophie"}, {"age", "20"}})
                 .BuildQuery();

    std::cout << query_b << '\n';

    return 0;
}
#include "sql_select_builder.hpp"

SqlSelectQueryBuilder&
SqlSelectQueryBuilder::AddColumn(std::string column_name)
{
    columns_.push_back(std::move(column_name));
    return *this;
}

SqlSelectQueryBuilder&
SqlSelectQueryBuilder::AddColumns(std::initializer_list<std::string> columns)
{
    for (const auto& column : columns)
    {
        AddColumn(column);
    }

    return *this;
}

SqlSelectQueryBuilder&
SqlSelectQueryBuilder::AddFrom(std::string table_name)
{
    table_name_ = std::move(table_name);
    return *this;
}

SqlSelectQueryBuilder&
SqlSelectQueryBuilder::AddWhere(std::string column_name, std::string value)
{
    where_conditions_.emplace_back(std::move(column_name), std::move(value));
    return *this;
}

SqlSelectQueryBuilder&
SqlSelectQueryBuilder::AddWhere(std::initializer_list<Condition> conditions)
{
    for (const auto& [column, value] : conditions)
    {
        AddWhere(column, value);
    }

    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const
{
    std::string query;
    query.reserve(DEFAULT_QUERY_RESERVE);

    query += "SELECT ";

    if (columns_.empty())
    {
        query.push_back('*');
    }
    else
    {
        AppendSeparated(query, columns_, ", ", [](auto& out, const auto& column)
        {
            out += column;
        });
    }

    query += " FROM ";
    query += table_name_;

    if (!where_conditions_.empty())
    {
        query += " WHERE ";

        AppendSeparated(query,where_conditions_, " AND ", [](auto& out, const auto& condition)
        {
            out += condition.first;
            out.push_back('=');
            out += condition.second;
        });
    }

    query.push_back(';');

    return query;
}

void SqlSelectQueryBuilder::Reset()
{
    columns_.clear();
    table_name_.clear();
    where_conditions_.clear();
}
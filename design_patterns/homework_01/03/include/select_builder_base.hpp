#pragma once

#include <exception>
#include <initializer_list>
#include <vector>
#include <string>
#include <string_view>

template<typename Derived>
class SelectBuilderBase
{
    protected:

        struct Condition
        {
            std::string column;
            std::string op;
            std::string value;
        };

        SelectBuilderBase() = default;

        void AppendCondition(const std::string& column, const std::string& op, const std::string& value)
        {
            where_conditions_.emplace_back(column, op, value);
        }

        Derived& Self()
        {
            return static_cast<Derived&>(*this);
        }

        const Derived& Self() const
        {
            return static_cast<const Derived&>(*this);
        }

    private:

        std::vector<std::string> columns_;
        std::string table_name_;
        std::vector<Condition> where_conditions_;

        static constexpr std::size_t DEFAULT_QUERY_RESERVE = 128;

        template<typename Container, typename Writer>
        void AppendSeparated(std::string& out, const Container& container, std::string_view separator, Writer writer) const
        {
            bool first = true;

            for (const auto& item : container)
            {
                if (!first)
                {
                    out += separator;
                }

                writer(out, item);

                first = false;
            }
        }

    public:

        Derived& Select(std::initializer_list<std::string> columns)
        {
            columns_.clear();
            columns_.reserve(columns.size());

            for (const auto& column : columns)
            {
                columns_.emplace_back(column);
            }

            return Self();
        }

        Derived& From(const std::string& table_name)
        {
            table_name_ = table_name;

            return Self();
        }

        Derived& Where(std::initializer_list<std::pair<std::string, std::string>> conditions)
        {
            for (const auto& [column, value] : conditions)
            {
                AppendCondition(column, "=", value);
            }

            return Self();
        }

        [[nodiscard]]
        std::string BuildQuery() const
        {
            if (table_name_.empty())
            {
                throw std::runtime_error("Table name cannot be empty");
            }

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

                AppendSeparated(query, where_conditions_, " AND ", [](std::string& out, const Condition& condition)
                {
                    out += condition.column;
                    out += condition.op;
                    out += condition.value;
                });
            }

            query += ";";

            return query;
        }
};
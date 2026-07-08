#pragma once

#include <initializer_list>
#include <vector>
#include <utility>
#include <string>
#include <string_view>


class SqlSelectQueryBuilder
{
    using Condition = std::pair<std::string, std::string>;

    private:

        std::vector<std::string> columns_;
        std::string table_name_;
        std::vector<Condition> where_conditions_;

        static constexpr std::size_t DEFAULT_QUERY_RESERVE = 128;

        template<typename Container, typename Writer>
        void AppendSeparated(std::string& out, const Container& container, const std::string_view separator, Writer writer) const
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

        SqlSelectQueryBuilder& AddColumn(std::string column_name);
        SqlSelectQueryBuilder& AddColumns(std::initializer_list<std::string> columns);

        SqlSelectQueryBuilder& AddFrom(std::string table_name);

        SqlSelectQueryBuilder& AddWhere(std::string column_name, std::string value);
        SqlSelectQueryBuilder& AddWhere(std::initializer_list<Condition> conditions);

        [[nodiscard]]
        std::string BuildQuery() const;

        void Reset();
};
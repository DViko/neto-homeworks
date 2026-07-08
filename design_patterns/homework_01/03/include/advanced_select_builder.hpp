#pragma once

#include "select_builder_base.hpp"

class AdvancedSelectBuilder : public SelectBuilderBase<AdvancedSelectBuilder>
{
    public:

        AdvancedSelectBuilder() = default;

        AdvancedSelectBuilder& WhereGreater(const std::string& column, const std::string& value)
        {
            AppendCondition(column, ">", value);

            return Self();
        }

        AdvancedSelectBuilder& WhereLess(const std::string& column, const std::string& value)
        {
            AppendCondition(column, "<", value);

            return Self();
        }
};
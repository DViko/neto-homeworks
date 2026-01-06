#pragma once

#include <string>
#include <vector>

struct IShapeParams
{
    std::string name;
    std::vector<int> edges;
    std::vector<int> angles;
};
#pragma once

#include <stdexcept>
#include <string>
#include <vector>


struct ShapeParams
{
    std::string name;
    std::vector<int> edges;
    std::vector<int> angles;
};


class LogicException : public std::logic_error
{
    public:

        explicit LogicException(const std::string& message) : std::logic_error(message)
        {
        }
};

class DomainException final : public LogicException
{
    public:

        using LogicException::LogicException;
};


class IShape
{
    public:

        virtual ~IShape() = default;
        virtual const ShapeParams& Params() const = 0;
};
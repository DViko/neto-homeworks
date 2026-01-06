#include <stdexcept>
#include <string>


class ShapeLogicException : public std::logic_error
{
    public:

        explicit ShapeLogicException(const std::string& message) : std::logic_error(message)
        {
        }
};

class ShapeDomainException final : public ShapeLogicException
{
    public:

        using ShapeLogicException::ShapeLogicException;
};
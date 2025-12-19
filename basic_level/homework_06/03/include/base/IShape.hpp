#ifndef ISHAPE_HPP
#define ISHAPE_HPP

class IShape
{
    public:

        virtual ~IShape() = default;
        virtual void Description() const = 0;
};

#endif
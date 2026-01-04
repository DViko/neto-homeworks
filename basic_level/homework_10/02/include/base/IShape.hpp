#pragma once

class IShape
{
    public:

        virtual ~IShape() = default;
        virtual void Description() const = 0;
};
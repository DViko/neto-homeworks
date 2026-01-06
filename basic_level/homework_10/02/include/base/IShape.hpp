#pragma once

#include "IShapeException.hpp"
#include "IShapeParams.hpp"

class IShape
{
    public:

        virtual ~IShape() = default;
        virtual const IShapeParams& Params() const = 0;
};
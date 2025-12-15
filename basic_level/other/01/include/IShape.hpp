#pragma once
#include <string>
#include "Descriptor.hpp"

class IShape
{
    protected:

        IShape(const std::string& name, unsigned int verticles_count);

    public:

        virtual ~IShape();

        virtual Descriptor ShapeDescriptor() const;
};
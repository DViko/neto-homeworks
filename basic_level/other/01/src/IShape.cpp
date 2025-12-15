#include <iostream>
#include "IShape.hpp"
#include "Descriptor.hpp"

class Shape : public IShape
{
    private:

        std::string _shape_name {};
        unsigned int _verticles_count {};

    protected:

        Shape(const std::string& name, unsigned int verticles_count);

    public:

        virtual ~Shape()
        {
            std::cout << "Destroying shape: " << _shape_name << '\n';
        }

        virtual Descriptor ShapeDescriptor() const override
        {
            return {_shape_name, _verticles_count};
        }
};
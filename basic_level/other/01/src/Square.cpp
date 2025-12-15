#include "IShape.hpp"

class Square : public IShape
{
    public:

        Square()
            : IShape("Square", 4)
        {
        }
};
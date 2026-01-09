#include "Quadrilaterals.hpp"
#include <stdexcept>


bool Quadrilateral::_CheckParams(const ShapeParams& params) const
{
    if (params.edges.size() != 4 || params.angles.size() != 4)
    {
        return false;
    }

    return 
            (params.angles[0] + params.angles[1] + params.angles[2] + params.angles[3] == 360);
}

Quadrilateral::Quadrilateral(ShapeParams params) : _params(std::move(params))
{
    if (!_CheckParams(_params))
    {
        throw LogicException("[logic exception]: Summ of angles in quadrilateral must be equal to 360 degrees");
    }
}

const ShapeParams& Quadrilateral::Params() const
{
    return _params;
}


Rectangle::Rectangle() : Quadrilateral({"Rectangle", {10, 20, 10, 20}, {90, 90, 90, 90}})
{
}

Square::Square() : Quadrilateral({"Square", {20, 20, 20, 20}, {90, 90, 70, 90}})
{
}
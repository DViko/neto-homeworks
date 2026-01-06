#include "quadrilaterals/AQuadrilateral.hpp"
#include <stdexcept>


bool AQuadrilateral::_CheckParams(const IShapeParams& params) const
{
    if (params.edges.size() != 4 || params.angles.size() != 4)
    {
        return false;
    }

    return 
            (params.angles[0] + params.angles[1] + params.angles[2] + params.angles[3] == 360);
}

AQuadrilateral::AQuadrilateral(IShapeParams params) : _params(std::move(params))
{
    if (!_CheckParams(_params))
    {
        throw ShapeLogicException("Summ of angles in quadrilateral must be equal to 360 degrees");
    }
}

const IShapeParams& AQuadrilateral::Params() const
{
    return _params;
}
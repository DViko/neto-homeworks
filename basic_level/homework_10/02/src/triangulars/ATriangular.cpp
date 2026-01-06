#include "triangulars/ATriangular.hpp"
#include <stdexcept>


bool ATriangular::_CheckEdges(IShapeParams params) const
{
    if (params.edges.size() != 3 || params.angles.size() != 3)
    {
        return false;
    }

    return
            (params.edges[0] > 0 && params.edges[1] > 0 && params.edges[2] > 0);
}

ATriangular::ATriangular(IShapeParams params) : _params(std::move(params))
{
    if (!_CheckEdges(_params))
    {
        throw ShapeLogicException("Edges of triangular parameters must be positive and greather than zero");
    }
}

const IShapeParams& ATriangular::Params() const
{
    return _params;
}
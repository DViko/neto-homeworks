#include "Triangulars.hpp"


bool Triangular::_CheckParams(const ShapeParams& params) const
{
    if (params.edges.size() != 3 || params.angles.size() != 3)
    {
        return false;
    }

    return
            (params.edges[0] > 0 && params.edges[1] > 0 && params.edges[2] > 0);
}

Triangular::Triangular(ShapeParams params) : _params(std::move(params))
{
    if (!_CheckParams(_params))
    {
        throw LogicException("[logic exception]: Edges of triangular parameters must be positive and greather than zero");
    }
}

const ShapeParams& Triangular::Params() const
{
    return _params;
}


Triangle::Triangle() : Triangular({"Triangle", {0, 12, 15}, {50, 60, 70}})
{
};

RightTriangle::RightTriangle() : Triangular({"Right triangle", {3, 4, 5}, {37, 53, 90}})
{
};
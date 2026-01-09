#pragma once

#include "IShape.hpp"

class Triangular : public IShape
{
    private:

        ShapeParams _params;

        bool _CheckParams(const ShapeParams& params) const;

    protected:

        Triangular(ShapeParams params);

    public:

        const ShapeParams& Params() const override final;
};


class Triangle final : public Triangular
{
    public:

        Triangle();
};

class RightTriangle final : public Triangular
{
    public:

        RightTriangle();
};
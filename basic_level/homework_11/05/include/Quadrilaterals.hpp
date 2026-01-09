#pragma once

#include "IShape.hpp"

class Quadrilateral : public IShape
{
    private:

        ShapeParams _params;

        bool _CheckParams(const ShapeParams& params) const;

    protected:

        Quadrilateral(ShapeParams params);

    public:

        const ShapeParams& Params() const override final;
};


class Rectangle final : public Quadrilateral
{
    public:

        Rectangle();
};

class Square final : public Quadrilateral
{
    public:

        Square();
};
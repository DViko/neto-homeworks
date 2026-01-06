#pragma once

#include "base/IShape.hpp"

class AQuadrilateral : public IShape
{
    private:

        IShapeParams _params;

        bool _CheckParams(const IShapeParams& params) const;

    protected:

        AQuadrilateral(IShapeParams params);

    public:

        const IShapeParams& Params() const override final;
};
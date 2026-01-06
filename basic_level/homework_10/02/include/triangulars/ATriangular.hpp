#pragma once

#include "base/IShape.hpp"

class ATriangular : public IShape
{
    private:

        IShapeParams _params;

        bool _CheckParams(const IShapeParams& params) const;

    protected:

        ATriangular(IShapeParams params);

    public:

        const IShapeParams& Params() const override final;
};
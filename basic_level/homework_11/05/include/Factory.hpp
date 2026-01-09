#pragma once

#include <IShape.hpp>

#ifdef __cplusplus

extern "C"
{

#endif

    struct IShape;

    enum class ShapeType
    {
        Triangle,
        RightTriangle,
        Rectangle,
        Square
    };

    IShape* CreateShape(ShapeType type);
    void DestroyShape(IShape* shape);

#ifdef __cplusplus

}

#endif
#include "Triangulars.hpp"
#include "Quadrilaterals.hpp"
#include "Factory.hpp"
#include "Logger.hpp"

#define FACTORY_API __attribute__((visibility("default")))

static Logger logger("app/shape_errors.log");

extern "C" FACTORY_API IShape* CreateShape(ShapeType type)
{
    try
    {
        switch (type)
        {
            case ShapeType::Triangle:
                return new Triangle();

            case ShapeType::RightTriangle:
                return new RightTriangle();

            case ShapeType::Rectangle:
                return new Rectangle();

            case ShapeType::Square:
                return new Square();

            default:
                return nullptr;
        }
    }
    catch (const LogicException& error)
    {
        logger.Log(error.what());
        return nullptr;
    }
}

extern "C" FACTORY_API void DestroyShape(IShape* shape)
{
    delete shape;
}
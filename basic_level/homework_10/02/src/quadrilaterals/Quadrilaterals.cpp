#include "quadrilaterals/Quadrilaterals.hpp"


Rectangle::Rectangle() : AQuadrilateral({"Rectangle", {10, 20, 10, 20}, {90, 90, 90, 90}})
{
};

Square::Square() : AQuadrilateral({"Square", {20, 20, 20, 20}, {90, 90, 70, 90}})
{
}
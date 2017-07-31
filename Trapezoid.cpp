/**
 * @file Trapezoid.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A File for the Trapezoid Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the Trapezoid Class implementation.
 * Define the Trapezoid Class, it's methods and fields.
 * A Trapezoid class is a specific Shape type which inherits from the abstract Shape.
 */


/*-----=  Includes  =-----*/


#include <cmath>
#include <algorithm>
#include "Trapezoid.h"


/*-----=  Definitions  =-----*/


/**
 * @def TRAPEZOID_POINTS 4
 * @brief A Macro that sets the valid number for Points in a Trapezoid.
 */
#define TRAPEZOID_POINTS 4

/**
 * @def TRAPEZOID_TYPE "Trapezoid"
 * @brief A Macro that sets the type name for the Trapezoid Shape.
 */
#define TRAPEZOID_TYPE "Trapezoid"


/*-----=  Constructors & Destructors  =-----*/


/**
 * @brief The Constructor of the Trapezoid.
 *        This Constructor receives a Vector of Points which will be the Trapezoid's vertices
 *        and create the Trapezoid from this Points, using the Shape's Constructor.
 *        The Constructor pass the Trapezoid type to the Shapes Constructor.
 *        If the number of Points is valid, the Constructor will calculate and update the
 *        area value of the Trapezoid.
 * @param points Vector of Points which will be the Trapezoid's vertices.
 */
Trapezoid::Trapezoid(const PointVector& points) : Shape(TRAPEZOID_TYPE, points)
{
    if (_points.size() == TRAPEZOID_POINTS)
    {
        _calculateArea();
    }
    // In case the number of Points is invalid, the area value will stay empty and the
    // validation functions will return false.
}


/*-----=  Trapezoid Methods  =-----*/


/**
 * @brief Calculates and updates the area of this Trapezoid.
 */
void Trapezoid::_calculateArea()
{
    auto i = _points.begin();
    Point p1 = *i++;
    Point p2 = *i++;
    Point p3 = *i++;
    Point p4 = *i;

    // We assume that the Trapezoids bases are parallel to the X axis.
    // Also, the order of the Vertices is p1 -> p2 -> p3 -> p4 -> p1.
    CordType baseA = fabs(p2.getX() - p1.getX());
    CordType baseB = fabs(p3.getX() - p4.getX());
    CordType height = fabs(p4.getY() - p1.getY());

    _area = ((baseA + baseB) * height) / 2;
}

/**
 * @brief Prints a representation of this Trapezoid.
 */
void Trapezoid::printShape() const
{
    auto i = _points.begin();

    CordType x1 = i -> getX();
    CordType y1 = i -> getY();
    i++;

    CordType x2 = i -> getX();
    CordType y2 = i -> getY();
    i++;

    CordType x3 = i -> getX();
    CordType y3 = i -> getY();
    i++;

    CordType x4 = i -> getX();
    CordType y4 = i -> getY();

    printTrapez(x1, y1, x2, y2, x3, y3, x4, y4);
}


/*-----=  Validate Trapezoid  =-----*/


/**
 * @brief Determine if the Trapezoid's orientation is valid, i.e. it does not contain 3 points
 *        with the same X or Y values and which form a line instead of a Triangle.
 * @return true if the Triangle's orientation is valid, false otherwise.
 */
bool Trapezoid::_validateOrientation() const
{
    auto i = _points.begin();
    const Point& p1 = *i++;
    const Point& p2 = *i++;
    const Point& p3 = *i++;
    const Point& p4 = *i;

    // Check that the first base is parallel to the X axis.
    if (fabs(p1.getY() - p2.getY()) > EPSILON)
    {
        return false;
    }
    // In this case, the first edge's Slope is valid, i.e. parallel to the X axis, i.e. the first
    // 2 points have the same Y value.
    CordType firstYValue = p1.getY();

    // Check that the second base is parallel to the X axis.
    if (fabs(p3.getY() - p4.getY()) > EPSILON)
    {
        return false;
    }
    // In this case, the second edge's Slope is valid, i.e. parallel to the X axis, i.e. the other
    // 2 points have the same Y value.
    CordType secondYValue = p3.getY();

    // Finally, we need to check if the 2 edges of the Trapezoid are not in the same Y value.
    return fabs(firstYValue - secondYValue) > EPSILON;
}

/**
 * @brief Determine if the Trapezoid's shape is valid.
 * @return true if the Trapezoid's shape is valid, false otherwise.
 */
bool Trapezoid::validateShape() const
{
    return _validatePoints(TRAPEZOID_POINTS) && _validateOrientation();
}


/**
 * @file Trapezoid.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A File for the Triangle Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the Triangle Class implementation.
 * Define the Triangle Class, it's methods and fields.
 * A Triangle class is a specific Shape type which inherits from the abstract Shape.
 */


/*-----=  Includes  =-----*/


#include <cmath>
#include "Triangle.h"


/*-----=  Definitions  =-----*/


/**
 * @def TRIANGLE_POINTS 3
 * @brief A Macro that sets the valid number for Points in a Triangle.
 */
#define TRIANGLE_POINTS 3

/**
 * @def TRIANGLE_TYPE "Triangle"
 * @brief A Macro that sets the type name for the Triangle Shape.
 */
#define TRIANGLE_TYPE "Triangle"


/*-----=  Constructors & Destructors  =-----*/


/**
 * @brief The Constructor of the Triangle.
 *        This Constructor receives a Vector of Points which will be the Triangle's vertices
 *        and create the Triangle from this Points, using the Shape's Constructor.
 *        The Constructor pass the Triangle type to the Shapes Constructor.
 *        If the number of Points is valid, the Constructor will calculate and update the
 *        area value of the Triangle.
 * @param points Vector of Points which will be the Triangle's vertices.
 */
Triangle::Triangle(const PointVector& points) : Shape(TRIANGLE_TYPE, points)
{
    if (_points.size() == TRIANGLE_POINTS)
    {
        _calculateArea();
    }
    // In case the number of Points is invalid, the area value will stay empty and the
    // validation functions will return false.
}


/*-----=  Triangle Methods  =-----*/


/**
 * @brief Calculates and updates the area of this Triangle.
 */
void Triangle::_calculateArea()
{
    auto i = _points.begin();
    Point p1 = *i++;
    Point p2 = *i++;
    Point p3 = *i;

    CordType k = DETERMINANT_FACTOR * _calculateDet(p1, p2, p3);
    _area = fabs(k);
}

/**
 * @brief Prints a representation of this Triangle.
 */
void Triangle::printShape() const
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

    printTrig(x1, y1, x2, y2, x3, y3);
}


/*-----=  Validate Triangle  =-----*/


/**
 * @brief Determine if the Triangle's shape is valid.
 * @return true if the Triangle's shape is valid, false otherwise.
 */
bool Triangle::validateShape() const
{
    return _validatePoints(TRIANGLE_POINTS) && _area != EMPTY_SHAPE_SIZE;
}

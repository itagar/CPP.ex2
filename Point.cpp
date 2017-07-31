/**
 * @file Point.cpp
 * @author Itai Tagar <itagar>
 * @version 1.7
 * @date 09 Sep 2016
 *
 * @brief A File for the Point Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the Point Class implementation.
 * Define the Point Class methods and fields.
 * A Point class is a single Point with X and Y coordinates in the plane.
 */


/*-----=  Includes  =-----*/


#include <cmath>
#include "Point.h"


/*-----=  Point Constructors & Destructors  =-----*/


/**
 * @brief A Constructor for the Point, which receive 2 coordinates and create a new Point in the
 *        plane with the given coordinates.
 * @param x The X coordinate in the plane.
 * @param y The Y coordinate in the plane.
 */
Point::Point(CordType const x, CordType const y)
{
    _x = x;
    _y = y;
}


/*-----=  Point Operators Overload  =-----*/


/**
 * @brief An operator overload for the comparison operator '==' which compares
 *        this Point with another given Point.
 * @param other A reference for the Point to compare to.
 * @return true if both the X coordinates and the Y coordinates are equal.
 */
bool Point::operator==(const Point& other) const
{
    // The X and Y coordinates are considered equal if their subtraction in absolute value
    // is smaller than EPSILON.
    bool xEquality = fabs((other.getX()) - (this -> getX())) <= EPSILON;
    bool yEquality = fabs((other.getY()) - (this -> getY())) <= EPSILON;

    // The Points are considered equal if both X and Y coordinates are equals.
    return xEquality && yEquality;
}

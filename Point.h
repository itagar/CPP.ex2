/**
 * @file Point.h
 * @author Itai Tagar <itagar>
 * @version 1.2
 * @date 09 Sep 2016
 *
 * @brief A Header File for the Point Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Point Class.
 * Declaring the Point Class, it's methods and fields.
 * A Point class is a single Point with X and Y coordinates in the plane.
 */


#ifndef POINT_H
#define POINT_H


/*-----=  Includes  =-----*/


#include "Defs.h"


/*-----=  Class Declaration  =-----*/


/**
 * @brief A Class representing a single Point with X and Y coordinates.
 *        The Point holds it's coordinates in the plane, and several methods that operates these
 *        coordinates.
 */
class Point
{
public:

    /**
     * @brief A Constructor for the Point, which receive 2 coordinates and create a new Point in the
     *        plane with the given coordinates.
     * @param x The X coordinate in the plane.
     * @param y The Y coordinate in the plane.
     */
    Point(CordType const x, CordType const y);

    /**
     * @brief Returns the X coordinate value.
     * @return The X coordinate value.
     */
    CordType getX() const { return _x; };

    /**
     * @brief Returns the Y coordinate value.
     * @return The Y coordinate value.
     */
    CordType getY() const { return _y; };

    /**
     * @brief An operator overload for the comparison operator '==' which compares
     *        this Point with another given Point.
     * @param other A reference for the Point to compare to.
     * @return true if both the X coordinates and the Y coordinates are equal.
     */
    bool operator==(const Point& other) const;

private:
    // Point Private Fields.
    CordType _x;  // The X coordinate value for the Point.
    CordType _y;  // The Y coordinate value for the Point.
};


#endif

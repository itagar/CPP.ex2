/**
 * @file Triangle.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A Header File for the Triangle Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Triangle Class.
 * Declaring the Triangle Class, it's methods and fields.
 * A Triangle class is a specific Shape type which inherits from the abstract Shape.
 */


#ifndef TRIANGLE_H
#define TRIANGLE_H


/*-----=  Includes  =-----*/


#include "Shape.h"


/*-----=  Definitions  =-----*/


/**
 * @brief A Class representing a Triangle Shape. The Triangle inherits from the Abstract Shape.
 *        A Shape holds it's Vertices and contains several methods which perform operations
 *        and calculations on the Shape.
 *        The Shape contains methods which involve another Shape to determine an intersections
 *        between the two.
 */
class Triangle : public Shape
{
public:

    /**
     * @brief The Constructor of the Triangle.
     *        This Constructor receives a Vector of Points which will be the Triangle's vertices
     *        and create the Triangle from this Points, using the Shape's Constructor.
     *        The Constructor pass the Triangle type to the Shapes Constructor.
     *        If the number of Points is valid, the Constructor will calculate and update the
     *        area value of the Triangle.
     * @param points Vector of Points which will be the Triangle's vertices.
     */
    Triangle(const PointVector& points);

    /**
     * @brief Determine if the Triangle's shape is valid.
     * @return true if the Triangle's shape is valid, false otherwise.
     */
    virtual bool validateShape() const override;

    /**
     * @brief Prints a representation of this Triangle.
     */
    virtual void printShape() const override;

private:

    /**
     * @brief Calculates and updates the area of this Triangle.
     */
    virtual void _calculateArea() override;

};


#endif

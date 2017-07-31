/**
 * @file Trapezoid.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A Header File for the Trapezoid Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Trapezoid Class.
 * Declaring the Trapezoid Class, it's methods and fields.
 * A Trapezoid class is a specific Shape type which inherits from the abstract Shape.
 */


#ifndef TRAPEZOID_H
#define TRAPEZOID_H


/*-----=  Includes  =-----*/


#include "Shape.h"


/*-----=  Definitions  =-----*/


/**
 * @brief A Class representing a Trapezoid Shape. The Trapezoid inherits from the Abstract Shape.
 *        A Shape holds it's Vertices and contains several methods which perform operations
 *        and calculations on the Shape.
 *        The Shape contains methods which involve another Shape to determine an intersections
 *        between the two.
 */
class Trapezoid : public Shape
{
public:

    /**
     * @brief The Constructor of the Trapezoid.
     *        This Constructor receives a Vector of Points which will be the Trapezoid's vertices
     *        and create the Trapezoid from this Points, using the Shape's Constructor.
     *        The Constructor pass the Trapezoid type to the Shapes Constructor.
     *        If the number of Points is valid, the Constructor will calculate and update the
     *        area value of the Trapezoid.
     * @param points Vector of Points which will be the Trapezoid's vertices.
     */
    Trapezoid(const PointVector& points);

    /**
     * @brief Determine if the Trapezoid's shape is valid.
     * @return true if the Trapezoid's shape is valid, false otherwise.
     */
    virtual bool validateShape() const override;

    /**
     * @brief Prints a representation of this Trapezoid.
     */
    virtual void printShape() const override;

private:

    /**
     * @brief Determine if the Trapezoid's orientation is valid, i.e. it does not contain 3 points
     *        with the same X or Y values and which form a line instead of a Triangle.
     * @return true if the Triangle's orientation is valid, false otherwise.
     */
    bool _validateOrientation() const;

    /**
     * @brief Calculates and updates the area of this Trapezoid.
     */
    virtual void _calculateArea() override;

};


#endif

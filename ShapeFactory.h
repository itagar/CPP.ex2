/**
 * @file ShapeFactory.h
 * @author Itai Tagar <itagar>
 * @version 1.0
 * @date 11 Sep 2016
 *
 * @brief A Shape Factory interface for creating a specific Shape using the Factory functions.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Shape Factory interface for creating a specific Shape using the Factory functions.
 * This Factory is based on the 'Factory Design Pattern'.
 * The Shape Factory holds all the different specific type
 */


#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


/*-----=  Includes  =-----*/


#include <vector>
#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"


/*-----=  Type Definitions  =-----*/


/**
 * @brief ShapeP is a pointer to a Shape.
 */
typedef Shape *ShapeP;


/*-----=  Enums  =-----*/


/**
 * @brief An Enum for the different types of Shapes.
 */
enum ShapeType
{
    INVALID_TYPE,
    TRIANGLE,
    TRAPEZOID
};


/*-----=  Shape Factory Methods  =-----*/


/**
 * @brief Determine the Shape's type in the given line from the input stream.
 * @param currentLine The given line that contains data from the input stream.
 * @return A ShapeType representing the current Shape's type.
 */
ShapeType getShapeType(const char typeFlag);

/**
 * @brief Create a Shape object of a specific type with the given type and coordinates.
 *        The Factory returns a pointer for the created Shape or Null Pointer in case of an error.
 * @param shapeType A ShapeType which represent the specific type of the Shape to create.
 * @param points The Points which create the Shape to create.
 * @return Pointer for the created Shape or Null Pointer in case of an error.
 */
ShapeP shapeFactory(ShapeType const shapeType, const PointVector& points);


#endif

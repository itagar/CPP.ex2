/**
 * @file ShapeFactory.cpp
 * @author Itai Tagar <itagar>
 * @version 1.0
 * @date 11 Sep 2016
 *
 * @brief A Shape Factory which creates a specific Shape using the Factory functions.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Shape Factory which creates a specific Shape using the Factory functions.
 * This Factory is based on the 'Factory Design Pattern'.
 * The Shape Factory holds all the different specific types of Shapes.
 */


/*-----=  Includes  =-----*/


#include "ShapeFactory.h"


/*-----=  Definitions  =-----*/


/**
 * @def TRIANGLE_TYPE_FLAG 'T'
 * @brief A Macro that sets the flag representing a Triangle type in the given line from a file.
 */
#define TRIANGLE_TYPE_FLAG 'T'

/**
 * @def TRAPEZOID_TYPE_FLAG 't'
 * @brief A Macro that sets the flag representing a Trapezoid type in the given line from a file.
 */
#define TRAPEZOID_TYPE_FLAG 't'


/*-----=  Shape Factory Methods  =-----*/


/**
 * @brief Determine the Shape's type in the given line from the input stream.
 * @param currentLine The given line that contains data from the input stream.
 * @return A ShapeType representing the current Shape's type.
 */
ShapeType getShapeType(const char typeFlag)
{
    switch (typeFlag)
    {
        case TRIANGLE_TYPE_FLAG:
            return TRIANGLE;

        case TRAPEZOID_TYPE_FLAG:
            return TRAPEZOID;

        default:
            return INVALID_TYPE;
    }
}

/**
 * @brief Create a Shape object of a specific type with the given type and coordinates.
 *        The Factory returns a pointer for the created Shape or Null Pointer in case of an error.
 * @param shapeType A ShapeType which represent the specific type of the Shape to create.
 * @param points The Points which create the Shape to create.
 * @return Pointer for the created Shape or Null Pointer in case of an error.
 */
ShapeP shapeFactory(ShapeType const shapeType, const PointVector& points)
{
    ShapeP pShape = nullptr;

    switch (shapeType)
    {
        case TRIANGLE:
            pShape = new Triangle(points);
            break;

        case TRAPEZOID:
            pShape = new Trapezoid(points);
            break;

        default:
            pShape = nullptr;
    }

    return pShape;
}

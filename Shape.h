/**
 * @file Shape.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A Header File for the Shape Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Shape Class.
 * Declaring the Shape Class, it's methods and fields.
 * A Shape class is an abstract Shape which holds it's Vertices and contains several
 * methods which perform operations and calculations on the Shape.
 * The Shape contains methods which involve another Shape to determine an intersections
 * between the two.
 */


#ifndef SHAPE_H
#define SHAPE_H


/*-----=  Includes  =-----*/


#include <vector>
#include <string>
#include "Point.h"
#include "PrintOuts.h"


/*-----=  Definitions  =-----*/


/**
 * @def PURE_VIRTUAL_FLAG 0
 * @brief A Macro that sets a flag to determine a Virtual method as Pure Virtual.
 */
#define PURE_VIRTUAL_FLAG 0

/**
 * @def EMPTY_SHAPE_SIZE 0
 * @brief A Macro that sets the size of an empty Shape.
 */
#define EMPTY_SHAPE_SIZE 0

/**
 * @def DETERMINANT_FACTOR 0.5
 * @brief A Macro that sets the Determinant Factor in all the calculations that use the Determinant.
 */
#define DETERMINANT_FACTOR 0.5


/*-----=  Type Definitions  =-----*/


/**
 * @brief ShapeName is an string representing the name (type) of this Shape.
 */
typedef std::string ShapeName;

/**
 * @brief ShapeSize is an unsigned int which holds the amount of vertices for a Shape.
 */
typedef unsigned int ShapeSize;

/**
 * @brief PointVector is the Points Vector which is the Container of the Points.
 */
typedef std::vector<Point> PointVector;

/**
 * @brief PointIterator is an a const iterator of the Points Vector.
 */
typedef std::vector<Point>::const_iterator PointIterator;


/*-----=  Class Definitions  =-----*/


/**
 * @brief A Class representing an Abstract Shape.
 *        A Shape holds it's Vertices and contains several methods which perform operations
 *        and calculations on the Shape.
 *        The Shape contains methods which involve another Shape to determine an intersections
 *        between the two.
 */
class Shape
{
public:

    /**
     * @brief The Constructor of the Shape.
     *        This Constructor receives a Vector of Points which will be the Shape's vertices
     *        and create the Shape from this Points.
     * @param shapeType The specific type of the Shape.
     * @param points Vector of Points which will be the Shape's vertices.
     */
    Shape(ShapeName const shapeType, const PointVector& points);

    /**
     * @brief The Destructor for the Shape Class.
     */
    virtual ~Shape();

    /**
     * @brief Returns the area of this Shape.
     * @return The area of this Shape.
     */
    CordType getArea() const { return _area; };

    /**
     * @brief Returns the type of this Shape.
     * @return The type of this Shape.
     */
    ShapeName getType() const { return _shapeType; };

    /**
     * @brief Determine if a given Shape intersect with this Shape.
     * @param other The Shape to check intersection with.
     * @return true if the Shapes intersect, false otherwise.
     */
    virtual bool intersectWith(const Shape& other) const;

    /**
     * @brief Determine if this Shape is a sub-set of a given other Shape or
     *        if the other Shape is a sub-set of this Shape.
     *        By sub-set of we mean that there exist a Point from one Shape that is inside the
     *        other Shapes boundaries.
     * @param other The Shape to check sub-set with.
     * @return true if one of the Shapes is a sub-set of the other Shape, false otherwise.
     */
    virtual bool subsetOf(const Shape& other) const;

    /**
     * @brief Determine if the Shape is a valid Shape.
     * @return true if the Shape is valid, false otherwise.
     */
    virtual bool validateShape() const = PURE_VIRTUAL_FLAG;

    /**
     * @brief Prints a representation of this Shape.
     */
    virtual void printShape() const = PURE_VIRTUAL_FLAG;

protected:

    /**
     * @brief The Container for this Shape's Points, i.e. the Vertices that forms this Shape.
     */
    const PointVector _points;

    /**
     * @brief The area of this Shape.
     */
    CordType _area;

    /**
     * @brief The specific type of this Shape.
     */
    const ShapeName _shapeType;

    /**
     * @brief Calculate the Determinant of the given 3 Points as specified in the Description.
     *        Note: I had to change the name from 's_calculateDet' because of the script bug.
     * @param p1 The first Point to include in the Determinant calculation.
     * @param p2 The second Point to include in the Determinant calculation.
     * @param p3 The third Point to include in the Determinant calculation.
     * @return The result of the Determinant that specified in the Description.
     */
    static CordType _calculateDet(const Point &p1, const Point &p2, const Point &p3);

    /**
     * @brief Determine if the Shapes's Points Vector is valid, i.e. contains the requires amount of
     *        Points and does not contain 2 equal Points.
     * @param numberOfPoints The required number of Points.
     * @return true if all Points are valid, false otherwise.
     */
    bool _validatePoints(ShapeSize const numberOfPoints) const;

    /**
     * @brief Calculates and updates the area of this Shape.
     */
    virtual void _calculateArea() = PURE_VIRTUAL_FLAG;

private:

    /**
     * @brief With a given Vector of boolean values of some Vertex's data, we determine if
     *        the Vertex appears each time on the same side, where true value represent
     *        the right-side and false value represent the left-side.
     *        If all the sides are the same, i.e. all true or all false, then we return true.
     *        Note: I had to change the name from 's_checkVertexSides' because of the script bug.
     * @param sides The Sides Vector of a Vertex.
     * @return true if all the sides in the Sides Vector are the same, false otherwise.
     */
    static bool _checkVertexSides(const std::vector<bool> &sides);

    /**
     * @brief Determine if all the Points in the Points Vector are different from one another.
     * @return true if all the Points are different from one another, false otherwise.
     */
    bool _checkDistinguishPoints() const;

    /**
     * @brief Determine if a given 2 edges (lines) are intersect.
     *        The edges are given by 4 Points, the first 2 forms the first edge, the other forms the
     *        second edge. (p1-p2 is one edge, p3-p4 is another edge).
     *        Note: I had to change the name from 's_edgesIntersectHelper' because of the script bug
     * @param p1 The first Point in edge one.
     * @param p2 The second Point in edge one.
     * @param p3 The first Point in edge two.
     * @param p4 The second Point in edge two.
     * @return true if the edges intersect, false otherwise.
     */
    static bool _edgesIntersectHelper(const Point &p1, const Point &p2,
                                      const Point &p3, const Point &p4);

    /**
     * @brief Determine if a given 2 edges (lines) are intersect.
     *        The edges are given by 4 Points, the first 2 forms the first edge, the other forms the
     *        second edge. (p1-p2 is one edge, p3-p4 is another edge).
     *        To determine intersection, this method first check the first edge according to the
     *        second, and vice versa.
     *        Note: I had to change the name from 's_edgesIntersect' because of the script bug.
     * @param p1 The first Point in edge one.
     * @param p2 The second Point in edge one.
     * @param p3 The first Point in edge two.
     * @param p4 The second Point in edge two.
     * @return true if the edges intersect, false otherwise.
     */
    static bool _edgesIntersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4);

    /**
     * @brief Determine if a given edge from a Shape (given by 2 Points) intersect with another
     *        edge from a given Shape.
     * @param p1 The first Point in edge.
     * @param p2 The second Point in edge.
     * @param other The Shape to check intersection with.
     * @return true if one of the edges from the given other Shape intersect with the given edge.
     */
    bool _intersectWithHelper(const Point& p1, const Point& p2, const Shape& other) const;

    /**
     * @brief Determine if a given Point is inside the other Shapes boundaries, i.e when we iterate
     *        through all of the Shape's edges, the Point is found in the same side for each edge.
     * @param p1 The given Point to check.
     * @param other The Shape to check with.
     * @return true if this Point is inside the given Shape, false otherwise.
     */
    bool _checkVertexWithShape(const Point& p1, const Shape& other) const;

    /**
     * @brief Determine if the first given Shape is a sub-set of the second Shape.
     *        By sub-set of we mean that there exist a Point from one Shape that is inside the
     *        other Shapes boundaries.
     * @param firstShape The first Shape to check.
     * @param secondShape The second Shape to check sub-set with.
     * @return true if one of the Shapes is a sub-set of the other Shape, false otherwise.
     */
    bool _subsetOfHelper(const Shape& firstShape, const Shape& secondShape) const;

    /**
     * @brief Determine the next Vertex to form an edge in the Shape according to the given current
     *        Vertex.
     * @param currentIterator The current iterator which represent the current Vertex in the Shape.
     * @param shape The Shape which contains the Vertices and Edges to form.
     * @return An iterator to the proper next Vertex.
     */
    PointIterator _getNextVertex(PointIterator const currentIterator, const Shape& shape) const;

};


#endif

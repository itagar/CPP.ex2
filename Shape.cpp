/**
 * @file Shape.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 12 Sep 2016
 *
 * @brief A File for the Shape Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the Shape Class implementation.
 * Define the Shape Class, it's methods and fields.
 * A Shape class is an abstract Shape which holds it's Vertices and contains several
 * methods which perform operations and calculations on the Shape.
 * The Shape contains methods which involve another Shape to determine an intersections
 * between the two.
 */


/*-----=  Includes  =-----*/


#include "Shape.h"


/*-----=  Constructors & Destructors  =-----*/

/**
 * @brief The Constructor of the Shape.
 *        This Constructor receives a Vector of Points which will be the Shape's vertices
 *        and create the Shape from this Points.
 * @param shapeType The specific type of the Shape.
 * @param points Vector of Points which will be the Shape's vertices.
 */
Shape::Shape(ShapeName const shapeType, const PointVector& points)
        : _points(points), _area(EMPTY_SHAPE_SIZE), _shapeType(shapeType)
{

}

/**
 * @brief The Destructor for the Shape Class.
 */
Shape::~Shape()
{

}


/*-----=  Shape Misc. Methods  =-----*/


/**
 * @brief Calculate the Determinant of the given 3 Points as specified in the Description.
 *        Note: I had to change the name from 's_calculateDet' because of the script bug.
 * @param p1 The first Point to include in the Determinant calculation.
 * @param p2 The second Point to include in the Determinant calculation.
 * @param p3 The third Point to include in the Determinant calculation.
 * @return The result of the Determinant that specified in the Description.
 */
CordType Shape::_calculateDet(const Point &p1, const Point &p2, const Point &p3)
{
    CordType x1 = p1.getX();
    CordType y1 = p1.getY();

    CordType x2 = p2.getX();
    CordType y2 = p2.getY();

    CordType x3 = p3.getX();
    CordType y3 = p3.getY();

    // Using the Rule of Sarrus.
    return ((x1 * y2) + (y1 * x3) + (x2 * y3) - (y2 * x3) - (y1 * x2) - (y3 * x1));
}

/**
 * @brief Determine the next Vertex to form an edge in the Shape according to the given current
 *        Vertex.
 * @param currentIterator The current iterator which represent the current Vertex in the Shape.
 * @param shape The Shape which contains the Vertices and Edges to form.
 * @return An iterator to the proper next Vertex.
 */
PointIterator Shape::_getNextVertex(PointIterator const currentIterator, const Shape& shape) const
{
    if (currentIterator == (shape._points.end() - 1))
    {
        // In case we reached the last Point, we need to form the edge that is connected
        // between this last Point and the first Point.
        return shape._points.begin();
    }
    else
    {
        // Create an edge between the current Point and the next Point.
        return currentIterator + 1;
    }
}


/*-----=  Shape Intersection  =-----*/


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
bool Shape::_edgesIntersectHelper(const Point &p1, const Point &p2,
                                  const Point &p3, const Point &p4)
{
    CordType firstPointSide = DETERMINANT_FACTOR * _calculateDet(p1, p3, p4);
    CordType secondPointSide = DETERMINANT_FACTOR * _calculateDet(p2, p3, p4);

    // If the result of this multiply is negative, it means that the values of the sides
    // have different signs (i.e. one is negative and one positive),
    // thus the two points of the first line are not on the same side of the other line.
    return firstPointSide * secondPointSide < 0;
}

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
bool Shape::_edgesIntersect(const Point &p1, const Point &p2,
                            const Point &p3, const Point &p4)
{
    return _edgesIntersectHelper(p1, p2, p3, p4) && _edgesIntersectHelper(p3, p4, p1, p2);
}

/**
 * @brief Determine if a given edge from a Shape (given by 2 Points) intersect with another
 *        edge from a given Shape.
 * @param p1 The first Point in edge.
 * @param p2 The second Point in edge.
 * @param other The Shape to check intersection with.
 * @return true if one of the edges from the given other Shape intersect with the given edge.
 */
bool Shape::_intersectWithHelper(const Point& p1, const Point& p2, const Shape& other) const
{
    PointIterator j;
    for (auto i = other._points.begin(); i != other._points.end(); i++)
    {
        // Determine the current edge to check using the 'i' and 'j' values.
        j = _getNextVertex(i, other);

        // For each edge in the given other Shape, we check the intersection with our given edge.
        if (_edgesIntersect(p1, p2, *i, *j))
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Determine if a given Shape intersect with this Shape.
 * @param other The Shape to check intersection with.
 * @return true if the Shapes intersect, false otherwise.
 */
bool Shape::intersectWith(const Shape& other) const
{
    PointIterator j;
    for (auto i = _points.begin(); i != _points.end(); i++)
    {
        // Determine the current edge to check using the 'i' and 'j' values.
        j = _getNextVertex(i, *this);

        // For each edge in this Shape, we check the intersection with any other edge
        // in the given other Shape.
        if (_intersectWithHelper(*i, *j, other))
        {
            return true;
        }
    }
    return false;
}


/*-----=  Shape Sub-Set  =-----*/


/**
 * @brief With a given Vector of boolean values of some Vertex's data, we determine if
 *        the Vertex appears each time on the same side, where true value represent
 *        the right-side and false value represent the left-side.
 *        If all the sides are the same, i.e. all true or all false, then we return true.
 *        Note: I had to change the name from 's_checkVertexSides' because of the script bug.
 * @param sides The Sides Vector of a Vertex.
 * @return true if all the sides in the Sides Vector are the same, false otherwise.
 */
bool Shape::_checkVertexSides(const std::vector<bool> &sides)
{
    for (auto i = sides.begin(); i != (sides.end() - 1); i++)
    {
        if (*i != *(i + 1))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Determine if a given Point is inside the other Shapes boundaries, i.e when we iterate
 *        through all of the Shape's edges, the Point is found in the same side for each edge.
 * @param p1 The given Point to check.
 * @param other The Shape to check with.
 * @return true if this Point is inside the given Shape, false otherwise.
 */
bool Shape::_checkVertexWithShape(const Point& p1, const Shape& other) const
{
    // Storing the different sides that the given Point appears in according to the Shapes edges.
    // The boolean value 'true' represent that the Point appears on the right side, and false
    // represent the left side.
    std::vector<bool> sides;

    PointIterator j;
    for (auto i = other._points.begin(); i != other._points.end(); i++)
    {
        // Determine the current edge to check using the 'i' and 'j' values.
        j = _getNextVertex(i, other);

        // For each edge in the given other Shape, we determine the side of the Point according to
        // the current edge.
        CordType k = DETERMINANT_FACTOR * _calculateDet(p1, *i, *j);
        sides.push_back((k < 0));  // True for right-side, false for left-side.
    }

    // Check that for all edges in the Shape, the Point appears on the same side of them.
    return _checkVertexSides(sides);
}

/**
 * @brief Determine if the first given Shape is a sub-set of the second Shape.
 *        By sub-set of we mean that there exist a Point from one Shape that is inside the
 *        other Shapes boundaries.
 * @param firstShape The first Shape to check.
 * @param secondShape The second Shape to check sub-set with.
 * @return true if one of the Shapes is a sub-set of the other Shape, false otherwise.
 */
bool Shape::_subsetOfHelper(const Shape& firstShape, const Shape& secondShape) const
{
    // We check if any Vertex from the first Shape is inside the second Shape.
    for (auto i = firstShape._points.begin(); i != firstShape._points.end(); i++)
    {
        if (_checkVertexWithShape(*i, secondShape))
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Determine if this Shape is a sub-set of a given other Shape or
 *        if the other Shape is a sub-set of this Shape.
 *        By sub-set of we mean that there exist a Point from one Shape that is inside the
 *        other Shapes boundaries.
 * @param other The Shape to check sub-set with.
 * @return true if one of the Shapes is a sub-set of the other Shape, false otherwise.
 */
bool Shape::subsetOf(const Shape& other) const
{
    return _subsetOfHelper(*this, other) || _subsetOfHelper(other, *this);
}


/*-----=  Validate Shape  =-----*/


/**
 * @brief Determine if all the Points in the Points Vector are different from one another.
 * @return true if all the Points are different from one another, false otherwise.
 */
bool Shape::_checkDistinguishPoints() const
{
    // Iterate through all the Points in the Points Vector to check that all points are different.
    for (auto i = _points.begin(); i != _points.end(); i++)
    {
        // Iterate one Point forward from the current starting Point in the outer loop.
        for (auto j = i + 1; j != _points.end(); j++)
        {
            if (*i == *j)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Determine if the Shapes's Points Vector is valid, i.e. contains the requires amount of
 *        Points and does not contain 2 equal Points.
 * @param numberOfPoints The required number of Points.
 * @return true if all Points are valid, false otherwise.
 */
bool Shape::_validatePoints(ShapeSize const numberOfPoints) const
{
    return (_points.size() == numberOfPoints) && (_checkDistinguishPoints());
}

/**
 * @file Shapes.cpp
 * @author Itai Tagar <itagar>
 * @version 1.7
 * @date 12 Sep 2016
 *
 * @brief The Shapes driver which runs the program to determine Shapes intersection from a given
 *        input file.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * The Shapes driver which runs the program to determine Shapes intersection
 * from a given input file.
 * Input:   The program receives File Streams as arguments.
 *          The first argument is the input file stream which contains the data of the Shapes to
 *          create and analyze.
 *          The second argument is the out file stream which the result of the program will appear
 *          in. This second argument is optional.
 * Process: The program validates the given streams first.
 *          If the streams are valid, the program process the data in the input file and create the
 *          required Shapes in addition to validating them.
 *          The program then analyze all the Shapes and determine if the there is an intersection
 *          between those Shapes.
 * Output:  If all the process of the program ran successfully, the program returns 0 and outputs
 *          the result of the analysis -
 *              1.  In case of intersection, the output will be the 2 Shapes that intersect
 *              2.  In case there is no intersection, the output will be the total area
 *                  of all the given Shapes.
 *          The output is the same for a given output file stream or to the standard output.
 *          If in some point there was an error in the program run (e.g. bad streams, illegal Shape)
 *          the program returns -1 and outputs to the standard error output an informative message.
 */


/*-----=  Includes  =-----*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include "ShapeFactory.h"


/*-----=  Definitions  =-----*/


/**
 * @def VALID_STATE 0
 * @brief A Macro that sets the value that returned in case the program ended successfully.
 */
#define VALID_STATE 0

/**
 * @def INVALID_STATE -1
 * @brief A Macro that sets the value that returned in case of failure during the program run.
 */
#define INVALID_STATE -1

/**
 * @def INPUT_ONLY_ARGUMENTS_SIZE 2
 * @brief A Macro that sets the number of arguments for input file only as an argument.
 */
#define INPUT_ONLY_ARGUMENTS_SIZE 2

/**
 * @def INPUT_OUTPUT_ARGUMENTS_SIZE 3
 * @brief A Macro that sets the number of arguments for input and output files as an arguments.
 */
#define INPUT_OUTPUT_ARGUMENTS_SIZE 3

/**
 * @def INPUT_FILE_INDEX 1
 * @brief A Macro that sets the index of the input file path in the given arguments.
 */
#define INPUT_FILE_INDEX 1

/**
 * @def OUTPUT_FILE_INDEX 2
 * @brief A Macro that sets the index of the output file path in the given arguments.
 */
#define OUTPUT_FILE_INDEX 2

/**
 * @def START_INDEX 0
 * @brief A Macro that sets the value for the start index in the input.
 */
#define START_INDEX 0

/**
 * @def SHAPE_TYPE_INDEX 0
 * @brief A Macro that sets the index of the Shape's type in the given line from a file.
 */
#define SHAPE_TYPE_INDEX 0

/**
 * @def COORDINATES_SEPARATOR '\t'
 * @brief A Macro that sets the flag representing the separator between the Shape's coordinates.
 */
#define COORDINATES_SEPARATOR '\t'

/**
 * @def INVALID_ARGUMENTS_MESSAGE "Usage: Shapes <input_file_name> [<output_file_name>]"
 * @brief A Macro that sets the output error message for invalid arguments.
 */
#define INVALID_ARGUMENTS_MESSAGE "Usage: Shapes <input_file_name> [<output_file_name>]"

/**
 * @def INVALID_FILE_MESSAGE "ERROR: Unable to open the file "
 * @brief A Macro that sets the output error message for invalid input file.
 */
#define INVALID_FILE_MESSAGE "ERROR: Unable to open the file "

/**
 * @def ILLEGAL_SHAPE_MESSAGE "ERROR: Illegal "
 * @brief A Macro that sets the output error message for invalid Shape coordinates.
 */
#define ILLEGAL_SHAPE_MESSAGE "ERROR: Illegal "

/**
 * @def INVALID_SHAPE_MESSAGE "ERROR: Invalid Shape Type."
 * @brief A Macro that sets the output error message for invalid Shape type.
 */
#define INVALID_SHAPE_MESSAGE "ERROR: Invalid Shape Type."

/**
 * @def DECIMAL_POINT_PRECISION 2
 * @brief A Macro that sets the number of digits after the decimal point in a number representation.
 */
#define DECIMAL_POINT_PRECISION 2


/*-----=  Type Definitions  =-----*/


/**
 * @brief ShapeVector is the ShapeP Vector which is the Container of the pointers for Shapes.
 */
typedef std::vector<ShapeP> ShapeVector;


/*-----=  Input Handling & Processing  =-----*/


/**
 * @brief Reports an error message to the standard error output in case of a
 *        bad stream (input/output).
 * @param stringName The name of the bad stream.
 */
static inline void reportStreamError(const std::string& stringName)
{
    std::cerr << INVALID_FILE_MESSAGE << stringName << std::endl;
    std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
}

/**
 * @brief Find the next coordinate in the given line and returns it's value as CordType.
 * @param currentLine The given line that contains data from the input stream.
 * @param currentIndex The current index in this process of analyzing the line.
 * @return A CordType which holds the value of the next coordinate.
 */
static CordType getCoordinate(std::string& currentLine, size_t& currentIndex)
{
    // Find the next coordinate.
    currentIndex = currentLine.find(COORDINATES_SEPARATOR);
    CordType coordinate = stod(currentLine.substr(START_INDEX, currentIndex));

    // Prepare the string for next call.
    currentLine = currentLine.substr(currentIndex + 1);

    return coordinate;
}

/**
 * @brief With a given line from the input stream, this function parse the line to the coordinates
 *        it holds. The function creates a Point from each set of coordinates and store it in the
 *        given Points Vector.
 * @param currentLine The given line that contains data from the input stream.
 * @param points The Points Vector which stores the Points for the current Shape.
 */
static void parseCoordinates(std::string& currentLine, PointVector& points)
{
    // Remove the redundant Token of the shape's type.
    size_t currentIndex = currentLine.find(COORDINATES_SEPARATOR);
    currentLine = currentLine.substr(currentIndex + 1);

    // Start iterating over the shape's coordinates.
    while (currentIndex != std::string::npos)
    {
        // Create the X and Y coordinates.
        CordType x = getCoordinate(currentLine, currentIndex);
        CordType y = getCoordinate(currentLine, currentIndex);

        // Create the current Point and add it to the Points Vector.
        Point currentPoint(x, y);
        points.push_back(currentPoint);
    }
}

/**
 * @brief Gets the Shape from the given line,
 *        The given line contains data of the current Shape, and the function creates the required
 *        Shape and returns a pointer for that Shape.
 * @param currentLine The current line in the input stream with the data of the Shape.
 * @return A pointer for the desired Shape, or NULL Pointer in case of an error.
 */
static ShapeP getShape(std::string& currentLine)
{
    ShapeP pShape = nullptr;
    PointVector points;

    // Determine the shape's type.
    char typeFlag = currentLine[SHAPE_TYPE_INDEX];
    const ShapeType shapeType = getShapeType(typeFlag);
    if (shapeType != INVALID_TYPE)
    {
        // Parse the current line into coordinates and update the Points Vector.
        parseCoordinates(currentLine, points);

        // Create the proper Shape object.
        pShape = shapeFactory(shapeType, points);
    }
    return pShape;

}

/**
 * @brief Update the given Shapes Vector with the given Shape Pointer to insert.
 *        If the given shape is invalid, the Vector will not be updated.
 * @param pShape A Shape Pointer to insert to the Shapes Vector.
 * @param shapes The Shapes Vector to update.
 * @return true if the Shape was inserted successfully, false otherwise.
 */
static bool updateShapes(const ShapeP& pShape, ShapeVector& shapes)
{
    if (pShape != nullptr)
    {
        if (pShape -> validateShape())
        {
            // Only valid Shapes can be inserted to the Shapes Vector.
            shapes.push_back(pShape);
            return true;
        }
    }
    return false;
}

/**
 * @brief Create and Store a new Shape in the given Shapes Vector.
 *        The function creates a new Shape from the given data in the current line and then
 *        attempt to insert it to the Shapes Vector.
 *        In case of invalid Shape, the Vector won't be updated and an error message will be printed
 *        to the output stream.
 * @param currentLine The current line in the input stream with the data of the Shape.
 * @param shapes The Shapes Vector to update.
 * @return true if the Shape was created and inserted successfully, false otherwise.
 */
static bool storeNewShape(std::string& currentLine, ShapeVector& shapes)
{
    // Create the current Shape from the given data in the line.
    ShapeP currentShape = nullptr;
    currentShape = getShape(currentLine);

    // Attempt to update the Shapes Vector with the new Shape if valid.
    // If the Shape is invalid, the Vector won't be updated and the function will return false.
    if (!updateShapes(currentShape, shapes))
    {
        // The case of invalid Shape.
        if (currentShape != nullptr)
        {
            // In this case, we still created a Shape but we didn't insert it in the Shapes Vector,
            // so we need to delete it here.
            std::cerr << ILLEGAL_SHAPE_MESSAGE << currentShape -> getType() << std::endl;
            delete currentShape;
        }
        else
        {
            std::cerr << INVALID_SHAPE_MESSAGE << std::endl;
        }
        return false;
    }

    return true;
}

/**
 * @brief Handles the input process.
 *        With the given input file stream, this function analyze the data to create all
 *        the proper Shapes that declared in the input file and store them for later use.
 * @param inputFile The input file stream to read from.
 * @param shapes The Shapes Vector which holds all the Shapes declared in the input file.
 * @return true if the program ended successfully, false otherwise.
 */
static bool handleInput(std::ifstream& inputFile, ShapeVector& shapes)
{
    std::string currentLine;
    while (std::getline(inputFile, currentLine))
    {
        // We ignore empty lines in the file.
        if (currentLine.empty())
        {
            continue;
        }

        // For each non-empty line in the file we create a Shape and store it in the Shapes Vector.
        if (!storeNewShape(currentLine, shapes))
        {
            return false;
        }
    }
    return true;
}


/*-----=  Analyze Shapes Data  =-----*/


/**
 * @brief Determine is there are Shapes that intersect with each other in our Shapes Container.
 *        If the function encountered an intersection, it will stop and report the first 2 Shapes
 *        that intersected, and return true.
 * @param shapes The Shapes Vector which holds the Shapes to check.
 * @return true if there is at least one intersection, false otherwise.
 */
static bool checkIntersection(const ShapeVector& shapes)
{
    // We compare each Shape in the Shapes Vector with all the other Shapes in the Vector.
    for (auto i = shapes.begin(); i != shapes.end(); i++)
    {
        for (auto j = i + 1; j != shapes.end(); j++)
        {
            // For each 2 Shapes, we check either one is a Sub-Set of the other, or that they
            // have some edges that intersect with each other.
            if ((*i) -> intersectWith(**j) || (*i) -> subsetOf(**j))
            {
                // We output only our first encounter of intersection.
                (*i) -> printShape();
                (*j) -> printShape();
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Calculate the total area of all the Shapes in the given Shapes Vector.
 * @param shapes The Shapes Vector which holds the Shapes to calculate their area.
 * @return the sum of all the Shapes' area.
 */
static CordType getTotalArea(const ShapeVector& shapes)
{
    CordType result = EMPTY_SHAPE_SIZE;
    for (auto i = shapes.begin(); i != shapes.end(); i++)
    {
        result += (*i) -> getArea();
    }
    return result;
}


/*-----=  Output Handling  =-----*/


/**
 * @brief Handles the output of the program according to the analysis of the given Shapes Vector.
 *        In case of an intersection, the program reports the intersection of the 2 Shapes,
 *        otherwise it just states the total area of all the Shapes.
 * @param shapes The Shapes Vector to analyze.
 */
static void handleOutput(const ShapeVector& shapes)
{
    if (checkIntersection(shapes))
    {
        reportDrawIntersect();
    }
    else
    {
        CordType totalArea = getTotalArea(shapes);
        printArea(totalArea);
    }
}

/**
 * @brief Frees all the resources and revert all changes that has been done during the run of
 *        the program.
 *        The function free all the resources from the given Shapes Vector, and assign back the
 *        original output stream.
 * @param shapes The Shapes Vector which contains Shapes to free.
 * @param originalStream The original output stream.
 */
static void freeResources(ShapeVector& shapes, std::streambuf *originalStream)
{
    // Free all the memory in the Shapes Vector that allocated by the ShapesFactory.
    for (auto i = shapes.begin(); i != shapes.end(); i++)
    {
        delete *i;
    }

    // Return the output stream back to normal.
    std::cout.rdbuf(originalStream);
}


/*-----=  Main  =-----*/


/**
 * @brief The main function that runs the program.
 *        The function receives 1-2 arguments, which determine the input stream and
 *        the output stream. The output stream is optional, and if not specified the output stream
 *        will be the standard output stream.
 *        Then the function analyze the input data, and process it to determine if there is an
 *        intersection between the given shapes.
 *        The function report to the output stream the result of the process.
 *        Note that all the File Streams are closed with the call of their Destructor.
 * @param argc The number of given arguments.
 * @param argv[] The arguments from the user.
 * @return 0 if the program ended successfully, -1 otherwise.
 */
int main(int argc, char *argv[])
{
    ShapeVector shapes;
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::streambuf *originalStream = std::cout.rdbuf();

    // Set the number representation precision.
    std::cout << std::fixed;
    std::cout << std::setprecision(DECIMAL_POINT_PRECISION);

    // Handle Arguments.
    if (argc == INPUT_OUTPUT_ARGUMENTS_SIZE)
    {
        // In this case we received an input file to read from, and and output file to write to.
        outputFile.open(argv[OUTPUT_FILE_INDEX]);
        if (!outputFile)
        {
            // If the given output file is an invalid file.
            reportStreamError(argv[OUTPUT_FILE_INDEX]);
            return INVALID_STATE;
        }
        std::cout.rdbuf(outputFile.rdbuf());  // Redirect the output stream to be the given file.
    }
    else if (argc != INPUT_ONLY_ARGUMENTS_SIZE)
    {
        // In this case we received invalid arguments.
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return INVALID_STATE;
    }

    // In this case we handle the input file stream.
    inputFile.open(argv[INPUT_FILE_INDEX]);
    if (!inputFile)
    {
        // If the given input file is an invalid file.
        reportStreamError(argv[INPUT_FILE_INDEX]);
        freeResources(shapes, originalStream);
        return INVALID_STATE;
    }

    // Analyze Data.
    if (handleInput(inputFile, shapes))
    {
        handleOutput(shapes);
        freeResources(shapes, originalStream);
        return VALID_STATE;
    }
    freeResources(shapes, originalStream);
    return INVALID_STATE;
}


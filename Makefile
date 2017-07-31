CXX= g++
CXXFLAGS= -c -Wextra -Wall -Wvla -pthread -std=c++11 -DNDEBUG
CODEFILES= ex2.tar Point.h Point.cpp Shape.h Shape.cpp Triangle.h Triangle.cpp Trapezoid.h  \
Trapezoid.cpp ShapeFactory.h ShapeFactory.cpp Shapes.cpp Defs.h PrintOuts.h PrintOuts.cpp Makefile README


# Default
default: Shapes


# Executables
Shapes: Shapes.o ShapeFactory.o PrintOuts.o Trapezoid.o Triangle.o Shape.o Point.o
	$(CXX) Shapes.o ShapeFactory.o Trapezoid.o Triangle.o Shape.o Point.o PrintOuts.o -o Shapes


# Object Files
Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) Point.cpp -o Point.o

Shape.o: Shape.cpp Shape.h Point.h PrintOuts.h
	$(CXX) $(CXXFLAGS) Shape.cpp -o Shape.o

Triangle.o: Triangle.cpp Triangle.h Shape.h
	$(CXX) $(CXXFLAGS) Triangle.cpp -o Triangle.o

Trapezoid.o: Trapezoid.cpp Trapezoid.h Shape.h
	$(CXX) $(CXXFLAGS) Trapezoid.cpp -o Trapezoid.o

ShapeFactory.o: ShapeFactory.cpp ShapeFactory.h Shape.h Triangle.h Trapezoid.h
	$(CXX) $(CXXFLAGS) ShapeFactory.cpp -o ShapeFactory.o

PrintOuts.o: PrintOuts.cpp PrintOuts.h
	$(CXX) $(CXXFLAGS) PrintOuts.cpp -o PrintOuts.o

Shapes.o: Shapes.cpp ShapeFactory.h
	$(CXX) $(CXXFLAGS) Shapes.cpp -o Shapes.o


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -vf *.o Shapes


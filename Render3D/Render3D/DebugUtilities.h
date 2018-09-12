#ifndef DEBUGUTILITIES_H
#define DEBUGUTILITIES_H

#include "Vec.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>

class DebugUtilities
{
public:
	DebugUtilities();
	virtual ~DebugUtilities();
	static void printVector(Vec& v);
	static void printMatrix(Matrix& m);
	static void writeCubeStl(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
};
#endif

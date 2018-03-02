#ifndef DEBUGUTILITIES_H
#define DEBUGUTILITIES_H

#include "Vec.h"
#include "Matrix.h"
#include <iostream>

class DebugUtilities
{
public:
	DebugUtilities();
	virtual ~DebugUtilities();
	static void printVector(Vec& v);
	static void printMatrix(Matrix& m);
};
#endif

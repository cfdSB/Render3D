#ifndef GEOMETRYUTILITY_H
#define GEOMETRYUTILITY_H

#include "Point3D.h"
#include "Matrix.h"
#include "Vec.h"
#include <iostream>
class GeometryUtility
{
public:
	GeometryUtility();
	virtual ~GeometryUtility();

	static float findDistance(const Point3D& point1, const Point3D& point2);
	static Vec transformVector(const Matrix& transformMat, const Vec& vec);
};
#endif

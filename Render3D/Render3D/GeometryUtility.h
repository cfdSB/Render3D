#ifndef GEOMETRYUTILITY_H
#define GEOMETRYUTILITY_H

#include "Point3D.h"
#include "Matrix.h"
#include "Vec.h"
#include <iostream>
#include <memory>
#include "GeometryEntity.h"
#include <vector>

class GeometryUtility
{
public:
	GeometryUtility();
	virtual ~GeometryUtility();

	static float findDistance(const Point3D& point1, const Point3D& point2);
	static Vec transformVector(const Matrix& transformMat, const Vec& vec);
	static std::unique_ptr<Point3D> computePlaneSegmentIntersection(const Vec& planeOrigin, const Vec& planeNormal, const Point3D& segmentPoint1, const Point3D& segmentPoint2);
	static bool isPointInsideTriangle(const Point3D& pnt, GeometryEntity::TriangleFace* triangleFace);
};
#endif

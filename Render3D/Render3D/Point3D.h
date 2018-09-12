#ifndef POINT3D_H
#define POINT3D_H

#include "Vec.h"
class Point3D
{
private:
	Vec * data;
	const int size = 3;

public:
	Point3D();
	Point3D(float xv, float yv, float zv);
	virtual ~Point3D();
	void setCoordinates(float xc, float yc, float zc);
	const Vec* getCoordinates() const { return data; };
	Point3D(const Point3D& p);
	Point3D& operator=(const Point3D& p);
};

#endif


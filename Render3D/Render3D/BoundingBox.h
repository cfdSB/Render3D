#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Point3D.h"
class BoundingBox
{
private:
	Point3D * lowestCorner; 
	Point3D *highestCorner;
	Point3D *centerPoint;
	bool initialized = false;
public:
	BoundingBox();
	~BoundingBox();
	const Point3D& getLowerLeftCorner() const { return *lowestCorner; };
	const Point3D& getUpperRightCorner() const { return *highestCorner; };
	const Point3D& getCenterPoint() const { return *centerPoint; };
	void setLowerLeftCorner(const Point3D& v);
	void setUpperRightCorner(const Point3D& v);
	void setInitialized(bool init) { initialized = init; };
	bool isInitialized() { return initialized; };

private:
	void updateCenterPoint();
};
#endif

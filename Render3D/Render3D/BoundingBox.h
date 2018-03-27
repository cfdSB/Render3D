#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Vec.h"
class BoundingBox
{
private:
	Vec lowestCorner = Vec(3);
	Vec highestCorner = Vec(3);
	Vec centerPoint = Vec(3);
	bool initialized = false;
public:
	BoundingBox();
	~BoundingBox();
	const Vec& getLowerLeftCorner() const { return lowestCorner; };
	const Vec& getUpperRightCorner() const { return highestCorner; };
	const Vec& getCenterPoint() const { return centerPoint; };
	void setLowerLeftCorner(const Vec& v);
	void setUpperRightCorner(const Vec& v);
	void setInitialized(bool init) { initialized = init; };
	bool isInitialized() { return initialized; };

private:
	void updateCenterPoint();
};
#endif

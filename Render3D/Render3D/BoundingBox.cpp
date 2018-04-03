#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
	lowestCorner = new Point3D();
	highestCorner = new Point3D();
	centerPoint = new Point3D();
}


BoundingBox::~BoundingBox()
{
	if (lowestCorner)
		delete lowestCorner;
	
	if (highestCorner)
		delete highestCorner;

	if (centerPoint)
		delete centerPoint;
}

void BoundingBox::setLowerLeftCorner(const Point3D & v)
{
	const Vec* coords = v.getCoordinates();
	lowestCorner->setCoordinates(coords->getElementAt(1), coords->getElementAt(2), coords->getElementAt(3));
	updateCenterPoint();
}

void BoundingBox::setUpperRightCorner(const Point3D & v)
{
	const Vec* coords = v.getCoordinates();
	highestCorner->setCoordinates(coords->getElementAt(1), coords->getElementAt(2), coords->getElementAt(3));
	updateCenterPoint();
}

void BoundingBox::updateCenterPoint()
{
	//update center point
	float centerX = (lowestCorner->getCoordinates()->getElementAt(1) + highestCorner->getCoordinates()->getElementAt(1)) / 2.0f;
	float centerY = (lowestCorner->getCoordinates()->getElementAt(2) + highestCorner->getCoordinates()->getElementAt(2)) / 2.0f;
	float centerZ = (lowestCorner->getCoordinates()->getElementAt(3) + highestCorner->getCoordinates()->getElementAt(3)) / 2.0f;

	centerPoint->setCoordinates(centerX, centerY, centerZ);
}

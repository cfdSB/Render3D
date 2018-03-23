#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::setLowerLeftCorner(const Vec & v)
{
	lowestCorner = v;
	updateCenterPoint();
}

void BoundingBox::setUpperRightCorner(const Vec & v)
{
	highestCorner = v;
	updateCenterPoint();
}

void BoundingBox::updateCenterPoint()
{
	//update center point
	float centerX = (lowestCorner.getElementAt(1) + highestCorner.getElementAt(1)) / 2.0f;
	float centerY = (lowestCorner.getElementAt(2) + highestCorner.getElementAt(2)) / 2.0f;
	float centerZ = (lowestCorner.getElementAt(3) + highestCorner.getElementAt(3)) / 2.0f;

	centerPoint.addElement(1, centerX).addElement(2, centerY).addElement(3, centerZ);
}

#include "GeometryUtility.h"



GeometryUtility::GeometryUtility()
{
}


GeometryUtility::~GeometryUtility()
{
}

float GeometryUtility::findDistance(const Point3D& point1, const Point3D& point2) {

	float xDiff = point1.getCoordinates()->getElementAt(1) - point2.getCoordinates()->getElementAt(1);
	float yDiff = point1.getCoordinates()->getElementAt(2) - point2.getCoordinates()->getElementAt(2);
	float zDiff = point1.getCoordinates()->getElementAt(3) - point2.getCoordinates()->getElementAt(3);
	float dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));

	return dist;
}

Vec GeometryUtility::transformVector(const Matrix & transformMat, const Vec & vec)
{
	Matrix pointsHolder(4, 1);
	pointsHolder.copyColumn(1, vec);
	pointsHolder.setAt(4, 1, 1.0);

	Matrix transformedVec = transformMat*pointsHolder;

	Vec newVec(3);
	newVec.addElement(1, transformedVec.getAt(1, 1)).addElement(2, transformedVec.getAt(2, 1)).addElement(3, transformedVec.getAt(3, 1));

	return newVec;
}

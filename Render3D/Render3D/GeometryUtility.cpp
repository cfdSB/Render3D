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

std::unique_ptr<Point3D> GeometryUtility::computePlaneSegmentIntersection(const Vec & planeOrigin, const Vec & planeNormal, const Point3D & segmentPoint1, const Point3D & segmentPoint2)
{
	Point3D* intersectionPoint = nullptr;
	std::unique_ptr<Point3D> intersectPoint;

	Vec u = *(segmentPoint2.getCoordinates()) - *(segmentPoint1.getCoordinates());
	Vec w = planeOrigin - *(segmentPoint1.getCoordinates());


	float norm1 = planeNormal * w;
	float norm2 = planeNormal * u;
	float intersectionInterval = norm1 / norm2;
	if (intersectionInterval >= 0.0 && intersectionInterval <= 1.0) {
		Vec pnt = *(segmentPoint1.getCoordinates()) + u.scale(intersectionInterval);
		intersectionPoint = new Point3D(pnt.getElementAt(1), pnt.getElementAt(2), pnt.getElementAt(3));
		intersectPoint.reset(intersectionPoint);
	}

	return intersectPoint;
}

bool GeometryUtility::isPointInsideTriangle(const Point3D & pnt, GeometryEntity::TriangleFace * triangleFace)
{
	bool status = false;
	std::vector<const Point3D*> trianglePoints = triangleFace->getPoints();
	const Vec v0 = *(trianglePoints.at(0)->getCoordinates());
	const Vec v1 = *(trianglePoints.at(1)->getCoordinates());
	const Vec v2 = *(trianglePoints.at(2)->getCoordinates());

	Vec u = v1 - v0;
	Vec v = v2 - v0;
	Vec w = *(pnt.getCoordinates()) - v0;

	float udotv = u * v;
	float wdotv = w * v;
	float vdotv = v * v;
	float wdotu = w * u;
	float udotu = u * u;

	float denom = udotv * udotv - udotu * vdotv;
	float s = (udotv * wdotv - vdotv * wdotu)/denom;
	float t = (udotv*wdotu - udotu*wdotv) / denom;

	if (s >= 0.0 && t >= 0.0 && (s + t) <= 1.0) {
		status = true; //point inside triangle
	}

	return status;
}

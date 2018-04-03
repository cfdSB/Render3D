#include "DisplayableObject.h"

DisplayableObject::DisplayableObject()
{
	box = new BoundingBox();
}

DisplayableObject::~DisplayableObject()
{
	for (Vec* v : vertexNormals) {
		if (v)
			delete v;
	}
	for (IndexedElement *it : indexedElements) {
		if (it)
			delete it;
	}

	for (Point3D *v : vertices) {
		if (v)
			delete v;
	}
}

void DisplayableObject::updateBoundingBox(Point3D& newPoint)
{
	float vx = newPoint.getCoordinates()->getElementAt(1);
	float vy = newPoint.getCoordinates()->getElementAt(2);
	float vz = newPoint.getCoordinates()->getElementAt(3);

	if (!box->isInitialized()) {
		Point3D firstPoint;
		firstPoint.setCoordinates(vx, vy, vz);
		box->setLowerLeftCorner(firstPoint);
		box->setUpperRightCorner(firstPoint);
		box->setInitialized(true);
		return;
	}

	float minX = box->getLowerLeftCorner().getCoordinates()->getElementAt(1);
	float minY = box->getLowerLeftCorner().getCoordinates()->getElementAt(2);
	float minZ = box->getLowerLeftCorner().getCoordinates()->getElementAt(3);

	float maxX = box->getUpperRightCorner().getCoordinates()->getElementAt(1);
	float maxY = box->getUpperRightCorner().getCoordinates()->getElementAt(2);
	float maxZ = box->getUpperRightCorner().getCoordinates()->getElementAt(3);

	bool minValuesUpdated = false;
	bool maxValuesUpdated = false;

	if (vx < minX) {
		minX = vx;
		minValuesUpdated = true;
	}
	else if (vx > maxX) {
		maxX = vx;
		maxValuesUpdated = true;
	}

	if (vy < minY) {
		minY = vy;
		minValuesUpdated = true;
	}
	else if (vy > maxY) {
		maxY = vy;
		maxValuesUpdated = true;
	}

	if (vz < minZ) {
		minZ = vz;
		minValuesUpdated = true;
	}
	else if (vz > maxZ) {
		maxZ = vz;
		maxValuesUpdated = true;
	}

	if (minValuesUpdated == true) {
		Point3D newLowerLeftCorner;
		newLowerLeftCorner.setCoordinates(minX, minY, minZ);
		box->setLowerLeftCorner(newLowerLeftCorner);
	}

	if (maxValuesUpdated == true) {
		Point3D newUpperRightCorner;
		newUpperRightCorner.setCoordinates(maxX, maxY, maxZ);
		box->setUpperRightCorner(newUpperRightCorner);
	}

}

void DisplayableObject::addVertex(float c1, float c2, float c3)
{
	Point3D *p = new Point3D(c1, c2, c3);
	vertices.push_back(p);

	updateBoundingBox(*p);
}

void DisplayableObject::addIndexedElement(IndexedElement *element)
{
	indexedElements.push_back(element);
}

void DisplayableObject::addNormal(float c1, float c2, float c3)
{
	Vec *normal = new Vec(3);
	normal->addElement(1, c1).addElement(2, c2).addElement(3, c3);
	vertexNormals.push_back(normal);
}

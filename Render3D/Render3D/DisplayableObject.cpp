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

	for (Vec *v : vertices) {
		if (v)
			delete v;
	}
}

void DisplayableObject::updateBoundingBox(Vec& newPoint)
{
	float vx = newPoint.getElementAt(1);
	float vy = newPoint.getElementAt(2);
	float vz = newPoint.getElementAt(3);

	float minX = box->getLowerLeftCorner().getElementAt(1);
	float minY = box->getLowerLeftCorner().getElementAt(2);
	float minZ = box->getLowerLeftCorner().getElementAt(3);

	float maxX = box->getUpperRightCorner().getElementAt(1);
	float maxY = box->getUpperRightCorner().getElementAt(2);
	float maxZ = box->getUpperRightCorner().getElementAt(3);

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
		Vec newLowerLeftCorner = Vec(3);
		newLowerLeftCorner.addElement(1, minX).addElement(2, minY).addElement(3, minZ);
		box->setLowerLeftCorner(newLowerLeftCorner);
	}

	if (maxValuesUpdated == true) {
		Vec newUpperRightCorner = Vec(3);
		newUpperRightCorner.addElement(1, maxX).addElement(2, maxY).addElement(3, maxZ);
		box->setUpperRightCorner(newUpperRightCorner);
	}

}

void DisplayableObject::addVertex(float c1, float c2, float c3)
{
	Vec *v = new Vec(3);
	v->addElement(1, c1).addElement(2, c2).addElement(3, c3);
	vertices.push_back(v);

	updateBoundingBox(*v);
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

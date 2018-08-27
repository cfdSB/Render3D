#include "DisplayableObject.h"

DisplayableObject::DisplayableObject(int verticesPerElement): verticesPerElement(verticesPerElement)
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

	for (IndexedElement *it : indexedEdges) {
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

void DisplayableObject::addIndexedEdge(IndexedElement * edge)
{
	indexedEdges.push_back(edge);
}

void DisplayableObject::addNormal(float c1, float c2, float c3)
{
	Vec *normal = new Vec(3);
	normal->addElement(1, c1).addElement(2, c2).addElement(3, c3);
	vertexNormals.push_back(normal);
}

std::unique_ptr<float[]> DisplayableObject::getVertexData() const
{
	unsigned int totalVertexCoordinates = getVertexCount() * coordinatesPerVertex;
	std::unique_ptr<float[]> vertexData(new float[totalVertexCoordinates]);

	unsigned int count = 0;
	for (const Point3D* p : getVertices()) {
		for (int i = 1; i <= p->getCoordinates()->getSize(); i++) {
			vertexData[count] = p->getCoordinates()->getElementAt(i);
			count++;
		}
	}

	return vertexData;
}

std::unique_ptr<unsigned int[]> DisplayableObject::getVertexIndexData() const
{
	unsigned int indicesPerElement = getElementIndexCount();
	unsigned int totalIndices = getIndexedElements().size() * indicesPerElement;
	std::cout << "Total indices DispObject:" << totalIndices << std::endl;
	std::unique_ptr<unsigned int[]> vertexIndexData(new unsigned int[totalIndices]);

	unsigned int indexCount = 0;
	for (const IndexedElement* p : getIndexedElements()) {
		//std::cout << "element index count: " << p->getIndexCount() << std::endl;
		for (int i = 0; i < indicesPerElement; i++) {
			vertexIndexData[indexCount] = p->getIndices()[i];
			indexCount++;
		}
	}

	return vertexIndexData;
}

std::unique_ptr<float[]> DisplayableObject::getNormalsData() const
{
	unsigned int totalNormalCoordinates = getVertexNormals().size()*coordinatesPerNormal;
	std::unique_ptr<float[]> normalsData(new float[totalNormalCoordinates]);

	unsigned int count = 0;
	for (const Vec* n : getVertexNormals()) {
		for (int i = 1; i <= n->getSize(); i++) {
			normalsData[count] = n->getElementAt(i);
			count++;
		}
	}

	return normalsData;
}

std::unique_ptr<unsigned int[]> DisplayableObject::getEdgeIndexData() const
{
	unsigned int indicesPerElement = getEdgeIndexCount();
	unsigned int totalIndices = getIndexedEdges().size() * indicesPerElement;
	std::cout << "Total Edge indices DispObject:" << totalIndices << std::endl;
	std::unique_ptr<unsigned int[]> edgeIndexData(new unsigned int[totalIndices]);

	unsigned int indexCount = 0;
	for (const IndexedElement* p : getIndexedEdges()) {
		//std::cout << "element index count: " << p->getIndexCount() << std::endl;
		for (int i = 0; i < indicesPerElement; i++) {
			edgeIndexData[indexCount] = p->getIndices()[i];
			indexCount++;
		}
	}

	return edgeIndexData;
}

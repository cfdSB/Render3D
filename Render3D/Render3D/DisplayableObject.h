#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include "Point3D.h"
#include "vector"
#include "IndexedElement.h"
#include "BoundingBox.h"
class DisplayableObject
{
private:
	std::vector<Point3D*> vertices;
	std::vector<Vec*> vertexNormals;
	std::vector<IndexedElement*> indexedElements;
	BoundingBox *box;
public:
	DisplayableObject();
	virtual ~DisplayableObject();

	const std::vector<Point3D*>& getVertices() const { return vertices; };
	const std::vector<IndexedElement*>& getIndexedElements() const { return indexedElements; };
	const std::vector<Vec*>& getVertexNormals() const { return vertexNormals; };
	const BoundingBox* getBoundingBox() const { return box; };
	size_t getVertexCount() { return vertices.size(); };
	virtual int getElementIndexCount() = 0;

	void addVertex(float c1, float c2, float c3);
	void addNormal(float c1, float c2, float c3);
	void addIndexedElement(IndexedElement* element);
private:
	void updateBoundingBox(Point3D& newPoint);
protected:
	
};

#endif

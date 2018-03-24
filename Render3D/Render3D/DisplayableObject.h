#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include "Vec.h"
#include "vector"
#include "IndexedElement.h"
#include "BoundingBox.h"
class DisplayableObject
{
private:
	std::vector<Vec*> vertices;
	std::vector<Vec*> vertexNormals;
	std::vector<IndexedElement*> indexedElements;
	BoundingBox *box;
public:
	DisplayableObject();
	virtual ~DisplayableObject();

	const std::vector<Vec*>& getVertices() const { return vertices; };
	const std::vector<IndexedElement*>& getIndexedElements() const { return indexedElements; };
	const std::vector<Vec*>& getVertexNormals() const { return vertexNormals; };
	const BoundingBox* getBoundingBox() const { return box; };
	size_t getVertexCount() { return vertices.size(); };
	virtual int getElementIndexCount() = 0;

	void addVertex(float c1, float c2, float c3);
	void addNormal(float c1, float c2, float c3);
	void addIndexedElement(IndexedElement* element);
private:
	void updateBoundingBox(Vec& newPoint);
protected:
	
};

#endif

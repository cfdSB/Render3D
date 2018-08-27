#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include "Point3D.h"
#include "vector"
#include "IndexedElement.h"
#include "BoundingBox.h"
#include <memory>
#include <iostream>

class DisplayableObject
{
private:
	int verticesPerElement;
	std::vector<Point3D*> vertices;
	std::vector<Vec*> vertexNormals;
	std::vector<IndexedElement*> indexedElements;
	std::vector<IndexedElement*> indexedEdges;	//to display mesh lines
	BoundingBox *box;

protected:

	const int coordinatesPerVertex = 3;
	const int coordinatesPerNormal = 3;
	const int verticesPerEdge = 2;

public:
	DisplayableObject(int verticesPerElement);
	virtual ~DisplayableObject();

	const BoundingBox* getBoundingBox() const { return box; };
	size_t getVertexCount() const { return vertices.size(); };
	int getElementIndexCount() const { return verticesPerElement; };
	int getEdgeIndexCount() const { return verticesPerEdge; };
	unsigned int getElementCount() const { return indexedElements.size(); };
	unsigned int getEdgeCount() const { return indexedEdges.size(); };

	virtual std::unique_ptr<float[]> getVertexData() const;
	virtual std::unique_ptr<unsigned int[]> getVertexIndexData() const;
	virtual std::unique_ptr<float[]> getNormalsData() const;
	virtual std::unique_ptr<unsigned int[]> getEdgeIndexData() const;

private:
	void updateBoundingBox(Point3D& newPoint);

protected:
	void addVertex(float c1, float c2, float c3);
	void addNormal(float c1, float c2, float c3);
	void addIndexedElement(IndexedElement* element);
	void addIndexedEdge(IndexedElement* edge);
	
	const std::vector<Point3D*>& getVertices() const { return vertices; };
	const std::vector<IndexedElement*>& getIndexedElements() const { return indexedElements; };
	const std::vector<Vec*>& getVertexNormals() const { return vertexNormals; };
	const std::vector<IndexedElement*>& getIndexedEdges() const { return indexedEdges; };
};

#endif

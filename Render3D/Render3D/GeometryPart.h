#ifndef GEOMETRYPART_H
#define GEOMETRYPART_H

#include <vector>
#include "Vec.h"
#include "IndexedTriangle.h"
#include "BoundingBox.h"
class GeometryPart
{
public:
	struct BoundingBox1 {
		Vec lowestCorner = Vec(3);
		Vec highestCorner = Vec(3);
		Vec centerPoint = Vec(3);
	};

private:
	typedef unsigned int uint;
	std::vector<Vec*> vertices;
	std::vector<IndexedTriangle*> triangles;
	std::vector<Vec*> faceNormals;
	BoundingBox box;

public:
	GeometryPart();
	virtual ~GeometryPart();
	size_t getVertexCount() { return vertices.size(); };
	size_t getTriangleCount() { return triangles.size(); };
	void addVertex(float c1, float c2, float c3);
	void addTriangle(uint i1, uint i2, uint i3);
	void addNormal(float c1, float c2, float c3);
	const std::vector<Vec*>* getVertices() const { return &vertices; };
	const std::vector<IndexedTriangle*>* getTriangles() const { return &triangles; };
	const std::vector<Vec*>* getFaceNormals() const { return &faceNormals; };
	const BoundingBox& getBoundingBox() const { return box; };
	

private:
	void updateBoundingBox(Vec& newPoint);
};

#endif

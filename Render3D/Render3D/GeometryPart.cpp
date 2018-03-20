#include "GeometryPart.h"



GeometryPart::GeometryPart()
{
}


GeometryPart::~GeometryPart()
{
	for (Vec* v : faceNormals) {
		if (v)
			delete v;
	}
	for (IndexedTriangle *it : triangles) {
		if (it)
			delete it;
	}
	
	for (Vec *v : vertices) {
		if (v)
			delete v;
	}
}

void GeometryPart::addVertex(float c1, float c2, float c3)
{
	Vec *v = new Vec(3);
	v->addElement(1, c1).addElement(2, c2).addElement(3, c3);
	vertices.push_back(v);
}

void GeometryPart::addTriangle(uint i1, uint i2, uint i3)
{
	IndexedTriangle *it = new IndexedTriangle(i1, i2, i3);
	triangles.push_back(it);
}

void GeometryPart::addNormal(float c1, float c2, float c3)
{
	Vec *normal = new Vec(3);
	normal->addElement(1, c1).addElement(2, c2).addElement(3, c3);
	faceNormals.push_back(normal);
}

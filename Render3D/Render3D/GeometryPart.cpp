#include "GeometryPart.h"

GeometryPart::GeometryPart() : DisplayableObject(3) // 3 vertices per element
{
}

GeometryPart::~GeometryPart()
{
}

void GeometryPart::addTriangleFace(float p1x, float p1y, float p1z, 
	                               float p2x, float p2y, float p2z, 
	                               float p3x, float p3y, float p3z, 
	                               float normalx, float normaly, float normalz)
{
	addVertex(p1x, p1y, p1z);
	addNormal(normalx, normaly, normalz);

	addVertex(p2x, p2y, p2z);
	addNormal(normalx, normaly, normalz);

	addVertex(p3x, p3y, p3z);
	addNormal(normalx, normaly, normalz);

	unsigned int totalPnts = getVertexCount();
	IndexedTriangle *it = new IndexedTriangle(totalPnts - 3, totalPnts - 2, totalPnts - 1);
	addIndexedElement(it);

	IndexedEdge *ie1 = new IndexedEdge(totalPnts - 3, totalPnts - 2);
	IndexedEdge *ie2 = new IndexedEdge(totalPnts - 2, totalPnts - 1);
	IndexedEdge *ie3 = new IndexedEdge(totalPnts - 1, totalPnts - 3);

	addIndexedEdge(ie1);
	addIndexedEdge(ie2);
	addIndexedEdge(ie3);
}


const std::vector<GeometryEntity::TriangleFace*> GeometryPart::getTriangleFaces() const
{
	std::vector<GeometryEntity::TriangleFace*> triangleFaces;

	const std::vector<IndexedElement*> elements = getIndexedElements();
	const std::vector<Vec*> normals = getVertexNormals();
	std::cout << "Total normals: " << normals.size() << std::endl;

	for (int i = 0; i < elements.size(); i++) {

		IndexedElement* triangle = elements.at(i);

		unsigned int p1Index = triangle->getIndices()[0];
		unsigned int p2Index = triangle->getIndices()[1];
		unsigned int p3Index = triangle->getIndices()[2];

		Point3D *pnt1 = getVertices().at(p1Index); 
		Point3D *pnt2 = getVertices().at(p2Index);
		Point3D *pnt3 = getVertices().at(p3Index);

		GeometryEntity::Edge *e1 = new GeometryEntity::Edge();
		e1->setPoints(pnt1, pnt2);
		GeometryEntity::Edge *e2 = new GeometryEntity::Edge();
		e2->setPoints(pnt2, pnt3);
		GeometryEntity::Edge *e3 = new GeometryEntity::Edge();
		e3->setPoints(pnt3, pnt1);

		GeometryEntity::TriangleFace* face = new GeometryEntity::TriangleFace();
		face->setEdges(e1, e2, e3);
		Vec* normal = normals.at(i*3);
		face->setNormal(normal);

		triangleFaces.push_back(face);	
	}

	return triangleFaces;
}






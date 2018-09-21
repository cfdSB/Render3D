#include "GeometryEntity.h"



GeometryEntity::GeometryEntity()
{
}


GeometryEntity::~GeometryEntity()
{
}

std::vector<GeometryEntity::Edge*> GeometryEntity::TriangleFace::getEdges() const
{
	std::vector<GeometryEntity::Edge*> edges;
	edges.push_back(edge1);
	edges.push_back(edge2);
	edges.push_back(edge3);

	return edges;
}

std::vector<const Point3D*> GeometryEntity::TriangleFace::getPoints() const
{
	std::vector<const Point3D*> points;
	for (Edge* e : getEdges()) {
		points.push_back(e->getPoint1());
	}
	return points;
}

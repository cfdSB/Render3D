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

#ifndef GEOMETRYENTITY_H
#define GEOMETRYENTITY_H

#include "Point3D.h"
#include <vector>
class GeometryEntity
{
public:
	GeometryEntity();
	~GeometryEntity();

	class Edge {
	private:
		Point3D *point1, *point2;
	public:
		Point3D * getPoint1() const { return point1; };
		Point3D* getPoint2() const { return point2; };
		void setPoints(Point3D* pnt1, Point3D* pnt2) { point1 = pnt1; point2 = pnt2; };
	};

	class TriangleFace {
	private:
		Edge * edge1, *edge2, *edge3;

	public:
		std::vector<GeometryEntity::Edge*> getEdges() const;
		void setEdges(GeometryEntity::Edge* e1, GeometryEntity::Edge* e2, GeometryEntity::Edge* e3) { edge1 = e1;
		edge2 = e2; edge3 = e3;
		};
	};
};

#endif


#include "PlaneSectionPart.h"





PlaneSectionPart::PlaneSectionPart(GeometryPart *part): DisplayableObject(2), part(part)
{
}


PlaneSectionPart::~PlaneSectionPart()
{
}

void PlaneSectionPart::computePlaneSection()
{
	const std::vector<GeometryEntity::TriangleFace*> triangleFaces = part->getTriangleFaces();

	std::vector<Point3D*> intersectPoints;

	for (GeometryEntity::TriangleFace* face : triangleFaces) {

		intersectPoints.clear();

		for(GeometryEntity::Edge * edge : face->getEdges()){
			Point3D* pointP1 = edge->getPoint1();
			Point3D* pointP2 = edge->getPoint2();
			Point3D* intersect = computePlaneIntersectionPoint(*pointP1, *pointP2);

			if (intersect != nullptr) {
				intersectPoints.push_back(intersect);
				//std::cout << " intersection point: " << intersect->getCoordinates()->getElementAt(1) << ","
				//	<< intersect->getCoordinates()->getElementAt(2) << "," << intersect->getCoordinates()->getElementAt(3) << std::endl;

			}
			/*else {
				std::cout << "No intersection Point" << std::endl;
			}*/
		}

		if (intersectPoints.size() >= 2) {
			Point3D* p1 = intersectPoints.at(0);
			addVertex(p1->getCoordinates()->getElementAt(1), p1->getCoordinates()->getElementAt(2), p1->getCoordinates()->getElementAt(3));
			addNormal(normal.getElementAt(1), normal.getElementAt(2), normal.getElementAt(3));

			Point3D* p2 = intersectPoints.at(1);
			addVertex(p2->getCoordinates()->getElementAt(1), p2->getCoordinates()->getElementAt(2), p2->getCoordinates()->getElementAt(3));
			addNormal(normal.getElementAt(1), normal.getElementAt(2), normal.getElementAt(3));

			unsigned int currentSize = this->getVertexCount();
			IndexedEdge *edge = new IndexedEdge(currentSize - 2, currentSize - 1);
			addIndexedElement(edge);
		}
	}
}

Point3D * PlaneSectionPart::computePlaneIntersectionPoint(const Point3D& p1, const Point3D& p2)
{
	Point3D* intersectionPoint = nullptr;
	
	Vec u = *(p2.getCoordinates()) - *(p1.getCoordinates());
	Vec w = origin - *(p1.getCoordinates());


	float norm1 = normal * w;
	float norm2 = normal * u;
	float intersectionInterval = norm1 / norm2;
	if (intersectionInterval >= 0.0 && intersectionInterval <= 1.0) {
		Vec pnt = *(p1.getCoordinates()) + u.scale(intersectionInterval);
		intersectionPoint = new Point3D(pnt.getElementAt(1), pnt.getElementAt(2), pnt.getElementAt(3));
	}

	return intersectionPoint;
}

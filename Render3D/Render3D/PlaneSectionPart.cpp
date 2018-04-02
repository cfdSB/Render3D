#include "PlaneSectionPart.h"




PlaneSectionPart::PlaneSectionPart(GeometryPart *part): part(part)
{
}


PlaneSectionPart::~PlaneSectionPart()
{
}

void PlaneSectionPart::computePlaneSection()
{
	const std::vector<Vec*> vertices = part->getVertices();
	const std::vector<IndexedElement*> elements = part->getTriangles();

	std::vector<Vec*> intersectPoints;
	for (IndexedElement *elm : elements) {
		intersectPoints.clear();
		for (int i = 0; i < elm->getIndexCount(); i++) {
			unsigned int p1IndexIndex, p2IndexIndex;
			unsigned int p1Index, p2Index;
			p1IndexIndex = i;
			p2IndexIndex = i + 1;
			if (p2IndexIndex >= elm->getIndexCount()) {
				p2IndexIndex = 0;
			}
			p1Index = elm->getIndices()[p1IndexIndex];
			p2Index = elm->getIndices()[p2IndexIndex];
			Vec *pointP1 = vertices.at(p1Index);
			Vec *pointP2 = vertices.at(p2Index);
			
			Vec* intersect = computePlaneIntersectionPoint(*pointP1, *pointP2);
			if (intersect != nullptr) {
				intersectPoints.push_back(intersect);
				std::cout << " intersection point: " << intersect->getElementAt(1) << ","
					<< intersect->getElementAt(2) << "," << intersect->getElementAt(3) << std::endl;
			}
			/*else {
				std::cout << "No intersection Point" << std::endl;
			}*/
		}

		if (intersectPoints.size() >= 2) {
			Vec* p1 = intersectPoints.at(0);
			addVertex(p1->getElementAt(1), p1->getElementAt(2), p1->getElementAt(3));
			addNormal(normal.getElementAt(1), normal.getElementAt(2), normal.getElementAt(3));

			Vec* p2 = intersectPoints.at(1);
			addVertex(p2->getElementAt(1), p2->getElementAt(2), p2->getElementAt(3));
			addNormal(normal.getElementAt(1), normal.getElementAt(2), normal.getElementAt(3));

			unsigned int currentSize = this->getVertexCount();
			IndexedEdge *edge = new IndexedEdge(currentSize - 2, currentSize - 1);
			addIndexedElement(edge);
		}
	}
}

Vec * PlaneSectionPart::computePlaneIntersectionPoint(const Vec& p1, const Vec& p2)
{
	Vec* intersectionPoint = nullptr;
	
	Vec u = p2 - p1;
	Vec w = origin - p1;

	float norm1 = normal * w;
	float norm2 = normal * u;
	float intersectionInterval = norm1 / norm2;
	if (intersectionInterval >= 0.0 && intersectionInterval <= 1.0) {
		Vec pnt = p1 + u.scale(intersectionInterval);
		intersectionPoint = new Vec(pnt);
	}

	return intersectionPoint;
}

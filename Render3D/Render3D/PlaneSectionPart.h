#ifndef PLANESECTIONPART_H
#define PLANESECTIONPART_H

#include "IndexedTriangle.h"
#include "DisplayableObject.h"
#include "GeometryPart.h"
#include "Vec.h"
#include <iostream>
#include "IndexedEdge.h"

class PlaneSectionPart : public DisplayableObject
{
private:
	const int PLANE_SECTION_PART_ELEMENT_INDEX_COUNT = 2;
	GeometryPart *part;
	Vec normal = Vec(3);
	Vec origin = Vec(3);

public:
	PlaneSectionPart(GeometryPart *part);
	virtual ~PlaneSectionPart();

	int getElementIndexCount() override {
		return PLANE_SECTION_PART_ELEMENT_INDEX_COUNT;
	};

	const Vec& getNormal() const { return normal; };
	const Vec& getOrigin() const { return origin; };
	void setNormal(const Vec& n) { normal = n; };
	void setOrigin(const Vec& orig) { origin = orig; };
	Point3D* computePlaneIntersectionPoint(const Point3D& p1, const Point3D& p2);
	void computePlaneSection();
private:
	//void computePlaneSection();
	//Vec* computePlaneIntersectionPoint(const Vec& p1, const Vec& p2);
};

#endif

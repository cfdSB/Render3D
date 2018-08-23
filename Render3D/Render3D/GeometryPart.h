#ifndef GEOMETRYPART_H
#define GEOMETRYPART_H

#include "IndexedTriangle.h"
#include "DisplayableObject.h"
#include "GeometryEntity.h"

class GeometryPart:public DisplayableObject
{
private:
	const int GEOM_PART_ELEMENT_INDEX_COUNT = 3;
public:
	GeometryPart();
	~GeometryPart();
	void addTriangleFace(float p1x, float p1y, float p1z,
		float p2x, float p2y, float p2z,
		float p3x, float p3y, float p3z,
		float normalx, float normaly, float normalz);

	const std::vector<GeometryEntity::TriangleFace*> getTriangleFaces() const;

};

#endif

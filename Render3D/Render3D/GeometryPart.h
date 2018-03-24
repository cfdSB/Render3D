#ifndef GEOMETRYPART_H
#define GEOMETRYPART_H

#include "IndexedTriangle.h"
#include "DisplayableObject.h"

class GeometryPart:public DisplayableObject
{
private:
	const int GEOM_PART_ELEMENT_INDEX_COUNT = 3;
public:
	GeometryPart();
	~GeometryPart();
	void addTriangle(unsigned int i1, unsigned int i2, unsigned int i3);
	const std::vector<IndexedElement*> getTriangles() { return getIndexedElements(); };
	int getElementIndexCount() override;
};

#endif

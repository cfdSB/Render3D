#include "GeometryPart.h"

GeometryPart::GeometryPart()
{
}

GeometryPart::~GeometryPart()
{
}


void GeometryPart::addTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
	IndexedTriangle *it = new IndexedTriangle(i1, i2, i3);
	addIndexedElement(it);
}

int GeometryPart::getElementIndexCount()
{
	return GEOM_PART_ELEMENT_INDEX_COUNT;
}


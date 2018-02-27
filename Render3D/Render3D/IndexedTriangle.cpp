#include "IndexedTriangle.h"



IndexedTriangle::IndexedTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
	 
	indices[0] = i1;
	indices[1] = i2;
	indices[2] = i3;
}

unsigned int* IndexedTriangle::getIndices()
{
	return indices;
}


IndexedTriangle::~IndexedTriangle()
{
}

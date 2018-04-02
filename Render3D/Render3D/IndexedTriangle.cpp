#include "IndexedTriangle.h"



IndexedTriangle::IndexedTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
	:IndexedElement(3)
{
	unsigned int* indices = getIndicesEditable();
	indices[0] = i1;
	indices[1] = i2;
	indices[2] = i3;
}

IndexedTriangle::IndexedTriangle()
	:IndexedTriangle(0,0,0)
{

}


IndexedTriangle::~IndexedTriangle()
{
}

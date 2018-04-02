#include "IndexedEdge.h"



IndexedEdge::IndexedEdge(unsigned int i1, unsigned int i2)
	:IndexedElement(2)
{
	unsigned int* indices = getIndicesEditable();
	indices[0] = i1;
	indices[1] = i2;
}


IndexedEdge::IndexedEdge()
	:IndexedEdge(0,0)
{
}


IndexedEdge::~IndexedEdge()
{
}

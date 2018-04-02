#ifndef INDEXEDEDGE_H
#define INDEXEDEDGE_H

#include "IndexedElement.h"
class IndexedEdge: public IndexedElement
{
public:
	IndexedEdge(unsigned int i1, unsigned int i2);
	IndexedEdge();
	virtual ~IndexedEdge();
};

#endif

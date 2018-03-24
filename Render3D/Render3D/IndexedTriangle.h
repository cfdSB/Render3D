#ifndef INDEXEDTRIANGLE_H
#define INDEXEDTRIANGLE_H
#include "IndexedElement.h"
class IndexedTriangle:public IndexedElement
{
private:
	
public:
	IndexedTriangle(unsigned int i1, unsigned int i2, unsigned int i3);
	IndexedTriangle();
	~IndexedTriangle();
};
#endif 

#ifndef INDEXEDTRIANGLE_H
#define INDEXEDTRIANGLE_H
class IndexedTriangle
{
private:
	unsigned int indices[3];
public:
	IndexedTriangle(unsigned int i1, unsigned int i2, unsigned int i3);
	unsigned int* getIndices();
	~IndexedTriangle();
};
#endif 

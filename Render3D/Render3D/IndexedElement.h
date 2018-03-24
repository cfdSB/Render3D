#ifndef INDEXEDELEMENT_H
#define INDEXEDELEMENT_H
class IndexedElement
{
private:
	unsigned int indexCount;
	unsigned int* indices;
public:
	virtual ~IndexedElement();
	unsigned int getIndexCount() const;
	virtual const unsigned int* getIndices() const;
protected:
	IndexedElement(unsigned int indexCount);
	unsigned int* getIndices();
};
#endif


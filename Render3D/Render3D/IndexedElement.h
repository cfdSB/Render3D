#ifndef INDEXEDELEMENT_H
#define INDEXEDELEMENT_H
class IndexedElement
{
private:
	int indexCount;
	unsigned int* indices;
public:
	virtual ~IndexedElement();
	int getIndexCount() const;
	virtual const unsigned int* getIndices() const;
protected:

	IndexedElement(int indexCount);

	unsigned int* getIndicesEditable();
};
#endif


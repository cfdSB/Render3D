#ifndef INDEXEDELEMENT_H
#define INDEXEDELEMENT_H
class IndexedElement
{
private:
	int indexCount;
	unsigned int elementID;
	unsigned int* indices;
public:
	virtual ~IndexedElement();
	int getIndexCount() const;
	virtual const unsigned int* getIndices() const;
	unsigned int getElementID() const { return elementID; };
	static unsigned int MAX_ID;
protected:

	IndexedElement(int indexCount);

	unsigned int* getIndicesEditable();
};
#endif


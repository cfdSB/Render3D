#include "IndexedElement.h"

unsigned int IndexedElement::MAX_ID;

IndexedElement::IndexedElement(int indexCount): indexCount(indexCount)
{
	indices = new unsigned int[indexCount];
	elementID = MAX_ID + 1;
	MAX_ID = elementID;
}

unsigned int * IndexedElement::getIndicesEditable()
{
	return indices;
}


IndexedElement::~IndexedElement()
{
	if (indices) {
		delete[] indices;
	}
}

int IndexedElement::getIndexCount() const
{
	return indexCount;
}

const unsigned int * IndexedElement::getIndices() const
{
	return indices;
}

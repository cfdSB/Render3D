#include "IndexedElement.h"



IndexedElement::IndexedElement(unsigned int indexCount): indexCount(indexCount)
{
	indices = new unsigned int[indexCount];
}

unsigned int * IndexedElement::getIndices()
{
	return indices;
}


IndexedElement::~IndexedElement()
{
	if (indices) {
		delete[] indices;
	}
}

unsigned int IndexedElement::getIndexCount() const
{
	return indexCount;
}

const unsigned int * IndexedElement::getIndices() const
{
	return indices;
}
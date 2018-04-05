#include "IndexedElement.h"



IndexedElement::IndexedElement(int indexCount): indexCount(indexCount)
{
	indices = new unsigned int[indexCount];
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

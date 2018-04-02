#include "Vec.h"
#include <math.h>

void Vec::initializeVector()
{
	for (int i = 0; i < size; i++) {
		data[i] = 0.0;
	}
}

Vec::Vec()
{
	data = nullptr;
}

Vec::Vec(int size): size(size)
{
	data = new float[size];
	initializeVector();
}


Vec::~Vec()
{
	if (data) {
		delete[] data;
	}
}

Vec::Vec(const Vec& v)
{
	size = v.size;
	data = new float[size];
	for (int i = 0; i < size; i++) {
		data[i] = v.data[i];
	}
}

Vec& Vec::operator=(const Vec& v)
{
	if (this == &v) {
		return *this;
	}
	if (data) {
		delete[] data;
	}

	size = v.size;
	data = new float[size];
	for (int i = 0; i < size; i++) {
		data[i] = v.data[i];
	}

	return *this;
}

Vec Vec::operator^(const Vec & v) const
{
	if (size == 3) {
		Vec cross(3);
		cross.addElement(1, (data[1] * v.data[2] - data[2] * v.data[1]));		//Ay*Bz - Az*By
		cross.addElement(2, (data[2] * v.data[0] - data[0] * v.data[2]));		//Az*Bx - Ax*Bz
		cross.addElement(3, (data[0] * v.data[1] - data[1] * v.data[0]));		//Ax*By - Ay*Bx

		return cross;
	}
	else {
		return Vec(size);
	}
	
}

Vec Vec::operator+(const Vec& v) const
{
	Vec newVec(v.size);
	for (int i = 0; i < size; i++) {
		newVec.data[i] = this->data[i] + v.data[i];
	}

	return newVec;
}

Vec Vec::operator-(const Vec & v) const
{
	Vec newVec(v.size);
	for (int i = 0; i < size; i++) {
		newVec.data[i] = this->data[i] - v.data[i];
	}

	return newVec;
}

float Vec::operator*(const Vec & v) const
{
	float dotProduct = 0.0;
	for (int i = 0; i < size; i++) {
		dotProduct = dotProduct + this->data[i] * v.data[i];
	}
	return dotProduct;
}

Vec & Vec::addElement(int index, float element)
{
	data[index - 1] = element;
	return *this;
}

Vec Vec::normalize()
{
	double magnitude = 0.0;
	for (int i = 0; i < size; i++) {
		magnitude = magnitude + pow(data[i], 2);
	}
	magnitude = sqrt(magnitude);

	Vec normVector(size);
	for (int i = 1; i <= size; i++) {
		normVector.addElement(i, data[i-1] / magnitude);
	}

	return normVector;
}

Vec Vec::scale(float val) const
{
	Vec scaled(size);
	for (int i = 1; i <= size; i++) {
		scaled.addElement(i, val*getElementAt(i));
	}

	return scaled;
}

void Vec::initializeElements(float value)
{
	for (int i = 0; i < size; i++) {
		data[i] = value;
	}

}

void Vec::copy(const Vec & v)
{
	int copysize=0;
	(this->size < v.size) ? copysize = this->size : copysize = v.size;

	for (int i = 0; i < copysize; i++) {
		data[i] = v.data[i];
	}
}

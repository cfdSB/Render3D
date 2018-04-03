#include "Point3D.h"



Point3D::Point3D()
{
	data = new Vec(size);

	for (int i = 0; i < size; i++) {
		data->addElement(i + 1, 0.0);
	}
}

Point3D::Point3D(float xv, float yv, float zv)
{
	data = new Vec(size);

	data->addElement(1,xv); 
	data->addElement(2,yv);
	data->addElement(3,zv);
}


Point3D::~Point3D()
{
	if (data) {
		delete[] data;
	}
}

void Point3D::setCoordinates(float xc, float yc, float zc)
{
	data->addElement(1, xc).addElement(2, yc).addElement(3, zc);
}

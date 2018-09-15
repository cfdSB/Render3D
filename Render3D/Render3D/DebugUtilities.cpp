#include "DebugUtilities.h"



DebugUtilities::DebugUtilities()
{
}


DebugUtilities::~DebugUtilities()
{
}

void DebugUtilities::printVector(Vec & v)
{
	for (int i = 1; i <= v.getSize(); i++) {
		std::cout << v.getElementAt(i) << " ";
	}
	std::cout << std::endl;
}

void DebugUtilities::printMatrix(Matrix & m)
{
	for (int i = 1; i <= m.getNumberOfRows(); i++) {
		for (int j = 1; j <= m.getNumberOfColumns(); j++) {
			std::cout << m.getAt(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void DebugUtilities::writeCubeStl(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
	std::ofstream file;
	file.open("cube_2.stl", std::ios::out | std::ios::binary);
	unsigned int totalTriangles = 12;
	float normal[3];
	float point1[3];
	float point2[3];
	float point3[3];
	unsigned short attrib;
	char header[80] = "Test cube";

	file.write(reinterpret_cast<const char*>(&header), sizeof(header));
	file.write(reinterpret_cast<const char*>(&totalTriangles), sizeof(unsigned int));

	//lengths
	float xlength = xmax - xmin;
	float ylength = ymax - ymin;
	float zlength = zmax - zmin;

	//triangle 1
	normal[0] = 0.0; normal[1] = -1.0; normal[2] = 0.0;
	point1[0] = xmin; point1[1] = ymin; point1[2] = zmin;
	point2[0] = xmin + xlength; point2[1] = ymin; point2[2] = zmin;
	point3[0] = xmin; point3[1] = ymin; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle 2
	normal[0] = 0.0; normal[1] = -1.0; normal[2] = 0.0;
	point1[0] = xmin + xlength; point1[1] = ymin; point1[2] = zmin;
	point2[0] = xmin + xlength; point2[1] = ymin ; point2[2] = zmin + zlength;
	point3[0] = xmin; point3[1] = ymin; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle3
	normal[0] = 1.0; normal[1] = 0.0; normal[2] = 0.0;
	point1[0] = xmin + xlength; point1[1] = ymin; point1[2] = zmin;
	point2[0] = xmin + xlength; point2[1] = ymin + ylength; point2[2] = zmin;
	point3[0] = xmin + xlength; point3[1] = ymin; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle4
	normal[0] = 1.0; normal[1] = 0.0; normal[2] = 0.0;
	point1[0] = xmin + xlength; point1[1] = ymin + ylength; point1[2] = zmin;
	point2[0] = xmin + xlength; point2[1] = ymin + ylength; point2[2] = zmin + zlength;
	point3[0] = xmin + xlength; point3[1] = ymin ; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle5
	normal[0] = 0.0; normal[1] = 1.0; normal[2] = 0.0;
	point1[0] = xmin + xlength; point1[1] = ymin + ylength; point1[2] = zmin;
	point2[0] = xmin; point2[1] = ymin + ylength; point2[2] = zmin;
	point3[0] = xmin + xlength; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle6
	normal[0] = 0.0; normal[1] = 1.0; normal[2] = 0.0;
	point1[0] = xmin; point1[1] = ymin + ylength; point1[2] = zmin;
	point2[0] = xmin; point2[1] = ymin + ylength; point2[2] = zmin + zlength;
	point3[0] = xmin + xlength; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle7
	normal[0] = -1.0; normal[1] = 0.0; normal[2] = 0.0;
	point1[0] = xmin; point1[1] = ymin + ylength; point1[2] = zmin;
	point2[0] = xmin; point2[1] = ymin; point2[2] = zmin;
	point3[0] = xmin; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle8
	normal[0] = -1.0; normal[1] = 0.0; normal[2] = 0.0;
	point1[0] = xmin; point1[1] = ymin; point1[2] = zmin;
	point2[0] = xmin; point2[1] = ymin; point2[2] = zmin + zlength;
	point3[0] = xmin; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle9
	normal[0] = 0.0; normal[1] = 0.0; normal[2] = -1.0;
	point1[0] = xmin; point1[1] = ymin; point1[2] = zmin;
	point2[0] = xmin; point2[1] = ymin + ylength; point2[2] = zmin;
	point3[0] = xmin + xlength; point3[1] = ymin + ylength; point3[2] = zmin;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle10
	normal[0] = 0.0; normal[1] = 0.0; normal[2] = -1.0;
	point1[0] = xmin + xlength; point1[1] = ymin + ylength; point1[2] = zmin;
	point2[0] = xmin + xlength; point2[1] = ymin; point2[2] = zmin;
	point3[0] = xmin; point3[1] = ymin; point3[2] = zmin;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle11
	normal[0] = 0.0; normal[1] = 0.0; normal[2] = 1.0;
	point1[0] = xmin; point1[1] = ymin; point1[2] = zmin + zlength;
	point2[0] = xmin + xlength; point2[1] = ymin; point2[2] = zmin + zlength;
	point3[0] = xmin; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	//triangle12
	normal[0] = 0.0; normal[1] = 0.0; normal[2] = 1.0;
	point1[0] = xmin + xlength; point1[1] = ymin; point1[2] = zmin + zlength;
	point2[0] = xmin + xlength; point2[1] = ymin + ylength; point2[2] = zmin + zlength;
	point3[0] = xmin; point3[1] = ymin + ylength; point3[2] = zmin + zlength;

	file.write(reinterpret_cast<const char*>(&normal), sizeof(normal));
	file.write(reinterpret_cast<const char*>(&point1), sizeof(point1));
	file.write(reinterpret_cast<const char*>(&point2), sizeof(point2));
	file.write(reinterpret_cast<const char*>(&point3), sizeof(point3));
	file.write(reinterpret_cast<const char*>(&attrib), sizeof(attrib));

	file.flush();
	file.close();

}

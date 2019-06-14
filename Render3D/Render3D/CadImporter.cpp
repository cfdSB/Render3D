#include "CadImporter.h"



CadImporter::CadImporter()
{
}


CadImporter::~CadImporter()
{
}


GeometryPart* CadImporter::importSTL(std::string & fileName)
{
	GeometryPart *part = nullptr;
	//------------
	//Read Binary STL file
	//------------
	std::ifstream file(fileName, std::ios::in | std::ios::binary);
	//std::ifstream file("plate.stl", std::ios::in | std::ios::binary);
	if (file.is_open()) {

		part = new GeometryPart();

		char* name = new char[80];
		file.read(name, 80);
		std::cout << "STL header is : " << name << std::endl;
		UINT32 totalTriangles;
		file.read(reinterpret_cast<char*>(&totalTriangles), sizeof(totalTriangles));
		std::cout << "Number of triangles: " << totalTriangles << std::endl;
		float normal[3], v1[3], v2[3], v3[3];
		UINT16 attrib;

		for (int i = 1; i <= totalTriangles; i++) {
			file.read(reinterpret_cast<char*>(&normal), sizeof(normal));
			file.read(reinterpret_cast<char*>(&v1), sizeof(v1));
			file.read(reinterpret_cast<char*>(&v2), sizeof(v2));
			file.read(reinterpret_cast<char*>(&v3), sizeof(v3));
			file.read(reinterpret_cast<char*>(&attrib), sizeof(attrib));
			/*std::cout << "(" << v1[0] << ", " << v1[1] << ", " << v1[2] << ")" << std::endl;
			std::cout << "(" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;
			std::cout << "(" << v3[0] << ", " << v3[1] << ", " << v3[2] << ")" << std::endl;*/
			part->addTriangleFace(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], v3[0], v3[1], v3[2],
				                  normal[0], normal[1], normal[2]);

		}
		delete[] name;
	}

	return part;
}

LeafMeshPart * CadImporter::importSTLData(std::string & fileName)
{
	LeafMeshPart *leafPart = nullptr;

	//------------
	//Read Binary STL file
	//------------
	std::ifstream file(fileName, std::ios::in | std::ios::binary);
	
	if (file.is_open()) {

		char* name = new char[80];
		file.read(name, 80);
		std::cout << "STL header is : " << name << std::endl;
		UINT32 totalTriangles;
		file.read(reinterpret_cast<char*>(&totalTriangles), sizeof(totalTriangles));
		std::cout << "Number of triangles: " << totalTriangles << std::endl;
		float normal[3], v1[3], v2[3], v3[3];
		UINT16 attrib;

		std::vector<TriangularFace*> *faces = new std::vector<TriangularFace*>();
		std::vector<Point3D*> *vertices = new std::vector<Point3D*>();

		for (int i = 1; i <= totalTriangles; i++) {
			file.read(reinterpret_cast<char*>(&normal), sizeof(normal));
			file.read(reinterpret_cast<char*>(&v1), sizeof(v1));
			file.read(reinterpret_cast<char*>(&v2), sizeof(v2));
			file.read(reinterpret_cast<char*>(&v3), sizeof(v3));
			file.read(reinterpret_cast<char*>(&attrib), sizeof(attrib));
			/*std::cout << "(" << v1[0] << ", " << v1[1] << ", " << v1[2] << ")" << std::endl;
			std::cout << "(" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;
			std::cout << "(" << v3[0] << ", " << v3[1] << ", " << v3[2] << ")" << std::endl;*/

			Point3D* vertex1 = new Point3D(v1[0], v1[1], v1[2]);
			Point3D* vertex2 = new Point3D(v2[0], v2[1], v2[2]);
			Point3D* vertex3 = new Point3D(v3[0], v3[1], v3[2]);

			vertices->push_back(vertex1);
			vertices->push_back(vertex2);
			vertices->push_back(vertex3);

			unsigned int vectorSize = vertices->size();

			Vec *faceNormal = new Vec(3);
			faceNormal->addElement(1, normal[0]).addElement(2, normal[1]).addElement(3, normal[2]);

			TriangularFace *face = new TriangularFace(vectorSize - 3, vectorSize - 2, vectorSize - 1, faceNormal);
			faces->push_back(face);
			
		}

		leafPart = new LeafMeshPart(faces, vertices);

		delete[] name;
	}


	return leafPart;
}

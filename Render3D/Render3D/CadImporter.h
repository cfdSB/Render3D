#ifndef CADIMPORTER_H
#define CADIMPORTER_H

#include <string>
#include <iostream>
#include <fstream>
#include "GeometryPart.h"
#include "LeafMeshPart.h"
#include <vector>
class CadImporter
{
public:
	typedef unsigned int UINT32;
	typedef unsigned short UINT16;
	CadImporter();
	~CadImporter();
	GeometryPart* importSTL(std::string& fileName);
	LeafMeshPart* importSTLData(std::string& fileName);
};
#endif


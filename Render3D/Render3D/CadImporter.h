#ifndef CADIMPORTER_H
#define CADIMPORTER_H

#include <string>
#include <iostream>
#include <fstream>
#include "GeometryPart.h"
class CadImporter
{
public:
	typedef unsigned int UINT32;
	typedef unsigned short UINT16;
	CadImporter();
	~CadImporter();
	GeometryPart* importSTL(std::string& fileName);
};
#endif


#include <iostream>
#include "Vec.h"
#include "Matrix.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "RenderWindow.h"
#include "RenderObject.h"
#include "IndexedTriangle.h"
#include <fstream>
#include <math.h>
#include "View.h"
#include "DebugUtilities.h"
#include "CadImporter.h"
#include "ShaderProgram.h"
#include "PlaneSectionPart.h"
#include "ShaderManager.h"

//---------
//method declarations
//----------
void readInputFile(std::string fileName);

//-------------------
//variables to hold input values read from an input file
//--------------------
std::string partFileName;
std::string createSectionCut;
std::string sectionNormal;
std::string sectionOrigin;


int main() {

	//write a test cube stl
	//DebugUtilities::writeCubeStl(1200.0, 800.0, 800.0, 1600.0, 1200.0, 1200.0);

	//--------------
	//read input file (no GUI for this project yet)
	//--------------
	readInputFile("input.txt");

	//-------------
	//read STL file specified in input.txt
	//-------------
	CadImporter importer;
	//std::string fileName = "classic_tea_pot.stl";
	std::string fileName = partFileName;

	GeometryPart *part = importer.importSTL(fileName);

	//-----
	//Bounding box and zoom off distance
	//-----
	Vec boundingBoxLower = *(part->getBoundingBox()->getLowerLeftCorner().getCoordinates());
	Vec boundingBoxHigher = *(part->getBoundingBox()->getUpperRightCorner().getCoordinates());
	Vec centerPoint = *(part->getBoundingBox()->getCenterPoint().getCoordinates());

	std::cout << "bounding box: " << std::endl;
	DebugUtilities::printVector(boundingBoxLower);
	DebugUtilities::printVector(boundingBoxHigher);
	DebugUtilities::printVector(centerPoint);

	//--------
	//compute plane section
	//---------
	PlaneSectionPart *pPart = nullptr;

	if (createSectionCut == "true") {
		pPart = new PlaneSectionPart(part);
		Vec normalV(3);
		normalV.addElement(1, 0.0).addElement(2, 1.0).addElement(3, 0.0);
		Vec origin(3);
		origin.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);
		pPart->setNormal(normalV);
		pPart->setOrigin(origin);
		pPart->computePlaneSection();
	}
	//-----------
	//initialize render window
	//-----------
	RenderWindow window;

	//-------
	//compile and link shader programs
	//-------
	//ShaderProgram shaderProg("vShader_transformations_color.vs", "fShader_transformations_color.fs");
	//ShaderProgram shaderProgMeshColor("vShader_transformations_color.vs", "fShader_transformations_meshcolor.fs");
	ShaderManager shaderManager;
	window.setShaderManager(&shaderManager);


	//-----
	//camera position and direction of looking to begin with
	//-----
	Vec cameraPosition(3);
	cameraPosition.addElement(1, 1400.0).addElement(2, 0.0).addElement(3, 1000.0);  
	Vec targetPoint(3);
	//targetPoint.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);
	targetPoint = centerPoint;

	window.setViewParameters(cameraPosition, targetPoint);
	window.setProjectionParameters(45.0, 800, 600);
	window.setViewProjectionType(View::PROJECTION_TYPE::Parallel);
	
	//--------debug output----------
	View view;
	view.setViewParameters(cameraPosition, targetPoint);
	view.setProjectionParameters(45.0, 800, 600);

	Matrix lookAt = view.getLookAtMatrix();
	std::cout << "Look At matrix:" << std::endl;
	DebugUtilities::printMatrix(lookAt);

	Matrix projectionMat = view.getProjectionMatrix();
	std::cout << "Projection matrix:" << std::endl;
	DebugUtilities::printMatrix(projectionMat);

	//----------
	//prepare data to render
	//----------
	RenderObject *ro = nullptr;
	
	if (createSectionCut == "true") {
		//ro = new RenderObject(pPart);
		//ro->setShaderProgram(shaderProg.getProgramID());
		////ro->setShaderMeshProgram(shaderProgMeshColor.getProgramID());
		//ro->setDrawType(2);	//2 for line data
	}
	else {
		ro = new RenderObject(part);
		//ro->setShaderProgram(shaderManager.getObjectDisplayShaderProgram());
		//ro->setShaderMeshProgram(shaderProgMeshColor.getProgramID());
		ro->setDrawType(1); //1 for triangular element data
	}
	
	//--------
	//add data to Render window
	//--------
	window.addRenderObject(ro);

	//---------
	//start render loop
	//---------
	window.startRenderLoop();



	return 0;
}

void readInputFile(std::string fileName) {

	std::ifstream inputFile(fileName);
	if (inputFile.is_open()) {
		std::string str;
		int lineNumber = 0;
		std::string commentMark = "#";
		while (std::getline(inputFile, str)) {

			if(str.compare(0, commentMark.length(), commentMark) == 0){
				continue; //since the line is a comment
			}

			if (str.empty() == true) {
				continue;  //empty string
			}

			if (lineNumber == 0) {
				partFileName = str;
			}else if (lineNumber == 1) {
				createSectionCut = str;
			}
			lineNumber++;
		}
	}
	inputFile.close();

}


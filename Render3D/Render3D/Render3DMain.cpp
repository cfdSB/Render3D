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

int main() {

	CadImporter importer;
	std::string fileName = "classic_tea_pot.stl";
	GeometryPart *part = importer.importSTL(fileName);

	//-----
	//Bounding box and zoom off distance
	//-----
	Vec boundingBoxLower = part->getBoundingBox()->getLowerLeftCorner();
	Vec boundingBoxHigher = part->getBoundingBox()->getUpperRightCorner();
	Vec centerPoint = part->getBoundingBox()->getCenterPoint();

	std::cout << "bounding box: " << std::endl;
	DebugUtilities::printVector(boundingBoxLower);
	DebugUtilities::printVector(boundingBoxHigher);
	DebugUtilities::printVector(centerPoint);

	//-----------
	//initialize render window
	//-----------
	RenderWindow window;

	//-------
	//compile and link shader programs
	//-------
	ShaderProgram shaderProg("vShader_transformations_color.vs", "fShader_transformations_color.fs");

	//-----
	//camera position and direction of looking to begin with
	//-----
	Vec cameraPosition(3);
	cameraPosition.addElement(1, 100.0).addElement(2, -100.0).addElement(3, 100.0);  //isometric +x,-y,+z
	Vec targetPoint(3);
	//targetPoint.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);
	targetPoint = centerPoint;

	window.setViewParameters(cameraPosition, targetPoint);
	window.setProjectionParameters(45.0, 800, 600);
	
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
	RenderObject *ro = new RenderObject(part);
	ro->setShaderProgram(shaderProg.getProgramID());
	ro->setDrawType(1); //1 for triangular element data

	//--------
	//add data to Render window
	//--------
	window.addRenderObject(ro);

	//---------
	//start render loop
	//---------
	window.startRenderLoop();

	delete ro;

	return 0;
}


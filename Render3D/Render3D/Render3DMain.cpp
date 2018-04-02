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

int main() {

	CadImporter importer;
	//std::string fileName = "classic_tea_pot.stl";
	std::string fileName = "fuel_tank.stl";
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

	//--------
	//compute plane section
	//---------
	PlaneSectionPart pPart(part);
	Vec normalV(3);
	normalV.addElement(1, 0.0).addElement(2, 1.0).addElement(3, 0.0);
	Vec origin(3);
	origin.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);
	pPart.setNormal(normalV);
	pPart.setOrigin(origin);
	pPart.computePlaneSection();

	/*Vec p1(3);
	p1.addElement(1, -1.0).addElement(2, 2.5).addElement(3, 2.8);
	Vec p2(3);
	p2.addElement(1, 1.0).addElement(2, 5.0).addElement(3, 5.6);
	Vec* intersect = pPart.computePlaneIntersectionPoint(p1, p2);
	if (intersect != nullptr) {
		std::cout << " intersection point: " << intersect->getElementAt(1) << ","
			<< intersect->getElementAt(2) << "," << intersect->getElementAt(3) << std::endl;
	}
	else {
		std::cout << "No intersection Point" << std::endl;
	}
*/

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
	//RenderObject *ro = new RenderObject(part);
	//ro->setShaderProgram(shaderProg.getProgramID());
	//ro->setDrawType(1); //1 for triangular element data

	RenderObject *ro = new RenderObject(&pPart);
	ro->setShaderProgram(shaderProg.getProgramID());
	ro->setDrawType(2);	//2 for lines

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


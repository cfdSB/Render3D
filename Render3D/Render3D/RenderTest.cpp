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

Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp, float positionScale);
Matrix convertGlmMatrix(glm::mat4& m);
Vec create4Dpoint(Vec& point);
Vec perspectiveDivision(Vec& p);
RenderObject createRenderObject(std::vector<Vec>& v, std::vector<IndexedTriangle>& triangleIindices, Matrix& projection, Matrix& view);
Vec findBoundingBox(std::vector<Vec>& allPoints);
Vec findCenterPoint(Vec& boundingBox);
float findFarthestPointDistance(std::vector<Vec>& allPoints, Vec& centerPoint);
float findZoomOffDistance(std::vector<Vec>& allPoints, Vec& centerPoint);

const char* getVertexShaderSource();
const char* getFragmentShaderSource(int);
int buildAndCompileVertexShader(const char* vShaderSource);
int buildAndCompileFragmentShader(const char* fragShaderSource);
int buildAndLinkShaderProgram(int vShader, int fragShader);

int vertexShader, fragmentShader1, fragmentShader2;
int shaderProgram1, shaderProgram2;
unsigned int VAO, VBO, EBO, vertexCount;

int main() {

	//-----
	//data in world coordinates
	//------
	std::vector<Vec> allPoints;
	std::vector<IndexedTriangle> triangles;

	//Vec p1(3);
	//p1.addElement(1, 2.5).addElement(2, 2.5).addElement(3, 0.0);
	//Vec p2(3);
	//p2.addElement(1, 3.5).addElement(2, 2.5).addElement(3, 0.0);
	//Vec p3(3);
	//p3.addElement(1, 2.5).addElement(2, 2.5).addElement(3, 2.0);
	//Vec p4(3);
	//p4.addElement(1, 3.5).addElement(2, 2.5).addElement(3, 2.0);

	//
	//allPoints.push_back(p1);
	//allPoints.push_back(p2);
	//allPoints.push_back(p3);
	//allPoints.push_back(p4);

	//
	//IndexedTriangle t1(0, 1, 2);
	//IndexedTriangle t2(1, 2, 3);
	//triangles.push_back(t1);
	//triangles.push_back(t2);

	//------------
	//Read Binary STL file
	//------------
	std::ifstream file("classic_tea_pot.stl", std::ios::in | std::ios::binary);
	if (file.is_open()) {
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
			Vec vert1(3);
			vert1.addElement(1, v1[0]).addElement(2, v1[1]).addElement(3, v1[2]);
			Vec vert2(3);
			vert2.addElement(1, v2[0]).addElement(2, v2[1]).addElement(3, v2[2]);
			Vec vert3(3);
			vert3.addElement(1, v3[0]).addElement(2, v3[1]).addElement(3, v3[2]);
	
			allPoints.push_back(vert1);
			allPoints.push_back(vert2);
			allPoints.push_back(vert3);
	
			unsigned int totalPnts = allPoints.size();
			IndexedTriangle tr(totalPnts - 3, totalPnts - 2, totalPnts - 1);
			triangles.push_back(tr);
		}
		delete[] name;
	}

	//-----
	//Bounding box and zoom off distance
	//-----
	Vec boundingBox = findBoundingBox(allPoints);
	std::cout << "bounding box: " << std::endl;
	DebugUtilities::printVector(boundingBox);

	Vec centerPoint = findCenterPoint(boundingBox);
	std::cout << "center point: " << std::endl;
	DebugUtilities::printVector(centerPoint);

	//------------------
	//Find ZoomOff Distance
	//--------------------
	float zoomOffDistance = findZoomOffDistance(allPoints, centerPoint);
	std::cout << "camera zoomOff distance: " << zoomOffDistance << std::endl;

	//-----------
	//initialize render window
	//-----------
	RenderWindow w;

	//-------
	//compile and link shader programs
	//-------
	const char* vertexShaderSource = getVertexShaderSource();
	vertexShader = buildAndCompileVertexShader(vertexShaderSource);
	const char* fragmentShaderSource = getFragmentShaderSource(1);
	fragmentShader1 = buildAndCompileFragmentShader(fragmentShaderSource);
	shaderProgram1 = buildAndLinkShaderProgram(vertexShader, fragmentShader1);
	const char* fragmentShaderSourceBlack = getFragmentShaderSource(2);
	fragmentShader2 = buildAndCompileFragmentShader(fragmentShaderSourceBlack);
	shaderProgram2 = buildAndLinkShaderProgram(vertexShader, fragmentShader2);


	//-----
	//camera position and direction of looking to begin with
	//-----

	float minY = boundingBox.getElementAt(3);
	Vec cameraPosition(3);
	cameraPosition.addElement(1, 100.0).addElement(2, -100.0).addElement(3, 100.0);  //isometric +x,-y,+z
	//cameraPosition.addElement(1, centerPoint.getElementAt(1)).addElement(2, minY).addElement(3, centerPoint.getElementAt(3));
	Vec targetPoint(3);
	//targetPoint.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);
	targetPoint = centerPoint;
	Vec tmpLookUp(3);
	tmpLookUp.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 1.0);

	//---------
	//world to eye space conversion matrix - view matrix
	//---------
	//Matrix lookAt = computeLookAt(cameraPosition, targetPoint, tmpLookUp, zoomOffDistance);
	View view;
	view.setViewParameters(cameraPosition, targetPoint);
	w.setViewParameters(cameraPosition, targetPoint);
	Matrix lookAt = view.getLookAtMatrix();
	std::cout << "Look At matrix:" << std::endl;
	DebugUtilities::printMatrix(lookAt);

	//-------------------
	//set zoom off view in current view direction
	//-------------------
	Vec direction = Vec(view.getCameraDirection());
	Vec zoomOffCameraPosition = direction.scale(zoomOffDistance) + targetPoint;
	view.setViewParameters(zoomOffCameraPosition, targetPoint);
	w.setViewParameters(zoomOffCameraPosition, targetPoint);
	lookAt = view.getLookAtMatrix();

	//-----------------
	//GLM lookup matrix for comparison with my Render3D matrix
	//-----------------
	glm::vec3 eye = glm::vec3(cameraPosition.getElementAt(1), cameraPosition.getElementAt(2), cameraPosition.getElementAt(3));
	glm::vec3 center = glm::vec3(targetPoint.getElementAt(1), targetPoint.getElementAt(2), targetPoint.getElementAt(3));
	glm::vec3 up = glm::vec3(tmpLookUp.getElementAt(1), tmpLookUp.getElementAt(2), tmpLookUp.getElementAt(3));
	glm::mat4 viewMat = glm::lookAt(eye, center, up);
	Matrix glmLookAt = convertGlmMatrix(viewMat);
	std::cout << "GLM look at matrix " << std::endl;
	DebugUtilities::printMatrix(glmLookAt);

	//------
	//eye space to clip space conversion matrix - projection matrix
	//------
	//glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, 0.1, 100.0);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	Matrix projectionMat = convertGlmMatrix(projection);
	std::cout << "Projection matrix:" << std::endl;
	DebugUtilities::printMatrix(projectionMat);

	//-------
	//Final transformation matrix
	//-------
	/*Matrix finalTransformMat = projectionMat * lookAt;
	std::cout << "Final Transform matrix:" << std::endl;
	printMatrix(finalTransformMat);*/

	//-------
	//Transform Coordinates
	//--------
	//std::vector<Vec> transformedPoints;
	//for (Vec& v : allPoints) {
	//	Vec point4D = create4Dpoint(v);
	//	Matrix pointMat(4, 1);
	//	pointMat.copyColumn(1, point4D);
	//	Matrix transformedP = finalTransformMat * pointMat;
	//	Vec transformedPnt = transformedP.getColumn(1);
	//	transformedPoints.push_back(transformedPnt);
	//}
	/*std::cout << " Transformed Points" << std::endl;
	for (Vec transP : transformedPoints) {
		printVector(transP);
	}*/

	//---------
	//clip space to NDC coordinates
	//---------
	//std::vector<Vec> ndcCoordinates;
	//for (Vec pt : transformedPoints) {
	//	Vec perspectiveDividedPnt = perspectiveDivision(pt);
	//	ndcCoordinates.push_back(perspectiveDividedPnt);
	//}

	//std::cout << " NDC Points" << std::endl;
	//for (Vec p : ndcCoordinates) {
	//	printVector(p);
	//}

	
	//----------
	//prepare data to render
	//----------
	RenderObject ro = createRenderObject(allPoints, triangles, projectionMat, lookAt);
	

	//--------
	//add data to Render window
	//--------
	w.addRenderObject(ro);
	w.startRenderLoop();

	return 0;
}

Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp, float positionScale) {

	Vec tmp = cameraPosition - targetPoint;
	std::cout << "tmp vector" << std::endl;
	DebugUtilities::printVector(tmp);
	Vec cameraDirection = tmp.normalize();
	std::cout << "camera direction" << std::endl;
	DebugUtilities::printVector(cameraDirection);

	Vec tmp2 = tmpLookUp ^ cameraDirection;
	Vec cameraRight = tmp2.normalize();
	std::cout << "camera Right" << std::endl;
	DebugUtilities::printVector(cameraRight);

	Vec tmp3 = cameraDirection ^ cameraRight;
	Vec cameraUp = tmp3.normalize();
	std::cout << "camera up" << std::endl;
	DebugUtilities::printVector(cameraUp);

	Matrix cameraCS(4, 4);
	cameraCS.copyRow(1, cameraRight);
	cameraCS.copyRow(2, cameraUp);
	cameraCS.copyRow(3, cameraDirection);
	std::cout << "Camera CS matrix" << std::endl;
	DebugUtilities::printMatrix(cameraCS);

	Matrix cameraPos(4, 4);
	Vec scaledCameraPosition = cameraDirection.scale(positionScale) + targetPoint;
	//Vec scaledCameraPosition = cameraPosition;
	Vec negCameraPosition = scaledCameraPosition.scale(-1.0);
	cameraPos.copyColumn(4, negCameraPosition);

	std::cout << "Camera neg pos matrix" << std::endl;
	DebugUtilities::printMatrix(cameraPos);

	Matrix lookAt = cameraCS * cameraPos;
	return lookAt;

}


Matrix convertGlmMatrix(glm::mat4& m) {
	Matrix convert(4, 4);

	for (int i = 1; i <= 4; i++) {
		glm::vec4 vect = glm::vec4(m[i - 1]);
		Vec v(4);
		for (int j = 1; j <= 4; j++) {
			v.addElement(j, vect[j - 1]);
		}
		convert.copyColumn(i, v);
	}

	return convert;
}

Vec create4Dpoint(Vec& point) {
	Vec p(4);
	p.initializeElements(1.0);
	p.copy(point);
	return p;
}

Vec perspectiveDivision(Vec& p) {
	Vec pDivPnt(3);
	for (int i = 1; i <= pDivPnt.getSize(); i++) {
		float val = p.getElementAt(i) / p.getElementAt(4);
		pDivPnt.addElement(i, val);
	}
	return pDivPnt;
}

RenderObject createRenderObject(std::vector<Vec>& points, std::vector<IndexedTriangle>& triangleIndices, Matrix& projection, Matrix& view) {
	int coordinatesPerPoint = points.at(0).getSize();
	int totalCoordinates = points.size() * coordinatesPerPoint;
	float* data = new float[totalCoordinates];

	int count = 0;
	for (Vec p : points) {
		for (int i = 1; i <= p.getSize(); i++) {
			data[count] = p.getElementAt(i);
			count++;
		}
	}

	unsigned int totalIndices = triangleIndices.size() * 3;
	unsigned int* indexData = new unsigned int[totalIndices];

	int indexCount = 0;
	for (IndexedTriangle p : triangleIndices) {
		for (int i = 0; i < 3; i++) {
			indexData[indexCount] = p.getIndices()[i];
			indexCount++;
		}
	}

	vertexCount = points.size();

		//float data[] = {
		//	-0.5f, -0.5f, 0.0f, // left  
		//	0.5f, -0.5f, 0.0f, // right 
		//	0.0f,  0.5f, 0.0f,  // top 
		//	0.5f, -0.5f, 0.0f,
		//	0.0f, 0.5f, 0.0f,
		//	0.7f, 0.7f, 0.0f
	
		//};
		//vertexCount = 6;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, totalCoordinates*sizeof(float), data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, coordinatesPerPoint, GL_FLOAT, GL_FALSE, coordinatesPerPoint * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram1);
	unsigned int uniformLocationProj = glGetUniformLocation(shaderProgram1, "projectionMat");
	glUniformMatrix4fv(uniformLocationProj, 1, GL_TRUE, projection.getDataPtr());
	
	unsigned int uniformLocationView = glGetUniformLocation(shaderProgram1, "viewMat");
	glUniformMatrix4fv(uniformLocationView, 1, GL_TRUE, view.getDataPtr());

	RenderObject rb(VAO, shaderProgram1, 1, vertexCount);
	return rb;
}

const char* getVertexShaderSource() {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 projectionMat;\n"
		"uniform mat4 viewMat;\n"
		"void main()\n"
		"{\n"
		//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, aPos.w);\n"
		"vec4 v = vec4(aPos, 1.0);\n"
		"gl_Position = projectionMat*viewMat*v;\n"
		"}\0";

	return vertexShaderSource;
}

const char* getFragmentShaderSource(int version) {
	const char* fragmentShaderSource = NULL;
	switch (version) {
	case 1: //orange color
		fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		break;
	case 2: //black color
		fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
			"}\n\0";
		break;
	}
	return fragmentShaderSource;
}

int buildAndCompileVertexShader(const char* vShaderSource) {
	int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glCompileShader(vShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return vShader;
}

int buildAndCompileFragmentShader(const char* fragShaderSource) {
	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return fragShader;
}

int buildAndLinkShaderProgram(int vShader, int fragShader) {
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);

	return shaderProgram;
}

Vec findBoundingBox(std::vector<Vec>& allPoints) {
	Vec boundingBox(6);
	
	float minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0;
	for (Vec& v : allPoints) {

		float vx = v.getElementAt(1);
		float vy = v.getElementAt(2);
		float vz = v.getElementAt(3);

		if (vx < minX) {
			minX = vx;
		} else if (vx > maxX) {
			maxX = vx;
		}

		if (vy < minY) {
			minY = vy;
		} else if (vy > maxY) {
			maxY = vy;
		}

		if (vz < minZ) {
			minZ = vz;
		} else if (vz > maxZ) {
			maxZ = vz;
		}
	}
	boundingBox.addElement(1, minX).addElement(2, maxX).addElement(3, minY).addElement(4, maxY).addElement(5, minZ).addElement(6, maxZ);
	return boundingBox;
}

Vec findCenterPoint(Vec& boundingBox) {
	Vec centerPoint(3);
	float centerX = (boundingBox.getElementAt(1) + boundingBox.getElementAt(2)) / 2.0f;
	float centerY = (boundingBox.getElementAt(3)+ boundingBox.getElementAt(4)) / 2.0f;
	float centerZ = (boundingBox.getElementAt(5) + boundingBox.getElementAt(6)) / 2.0f;

	centerPoint.addElement(1, centerX).addElement(2, centerY).addElement(3, centerZ);

	return centerPoint;
}

float findFarthestPointDistance(std::vector<Vec>& allPoints, Vec & centerPoint)
{
	float maxDist = 0.0;

	for (Vec& v : allPoints) {
		float xDiff = v.getElementAt(1) - centerPoint.getElementAt(1);
		float yDiff = v.getElementAt(2) - centerPoint.getElementAt(2);
		float zDiff = v.getElementAt(3) - centerPoint.getElementAt(3);
		float dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));
		if (dist > maxDist) {
			maxDist = dist;
		}
	}

	return maxDist;
}

float findZoomOffDistance(std::vector<Vec>& allPoints, Vec & centerPoint)
{
	float farthestPoint = findFarthestPointDistance(allPoints, centerPoint);
	std::cout << "farthest point distance: " << farthestPoint << std::endl;

	float perspectiveAngle = 45.0; //in degrees
	float PI = 3.14159265;
	float positionScale = farthestPoint / tan(perspectiveAngle / 2.0*PI / 180.0);

	return positionScale;
}

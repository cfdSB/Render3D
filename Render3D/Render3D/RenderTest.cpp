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

Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp);
void printMatrix(Matrix& m);
void printVector(Vec& v);
Matrix convertGlmMatrix(glm::mat4& m);
Vec create4Dpoint(Vec& point);
Vec perspectiveDivision(Vec& p);
RenderObject createRenderObject(std::vector<Vec>& v, std::vector<IndexedTriangle>& triangleIindices);

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
	Vec p1(3);
	p1.addElement(1, 2.5).addElement(2, 2.5).addElement(3, 0.0);
	Vec p2(3);
	p2.addElement(1, 3.5).addElement(2, 2.5).addElement(3, 0.0);
	Vec p3(3);
	p3.addElement(1, 2.5).addElement(2, 2.5).addElement(3, 2.0);
	Vec p4(3);
	p4.addElement(1, 3.5).addElement(2, 2.5).addElement(3, 2.0);

	std::vector<Vec> allPoints;
	allPoints.push_back(p1);
	allPoints.push_back(p2);
	allPoints.push_back(p3);
	allPoints.push_back(p4);

	std::vector<IndexedTriangle> triangles;
	IndexedTriangle t1(0, 1, 2);
	IndexedTriangle t2(1, 2, 3);
	triangles.push_back(t1);
	triangles.push_back(t2);

	//-----
	//camera position and direction of looking
	//-----
	Vec cameraPosition(3);
	cameraPosition.addElement(1, 3.0).addElement(2, -2.5).addElement(3, 1.0);
	Vec targetPoint(3);
	targetPoint.addElement(1, 3.0).addElement(2, 2.75).addElement(3, 1.0);
	Vec tmpLookUp(3);
	tmpLookUp.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 1.0);

	//---------
	//world to eye space conversion matrix - view matrix
	//---------
	Matrix lookAt = computeLookAt(cameraPosition, targetPoint, tmpLookUp);
	std::cout << "Look At matrix:" << std::endl;
	printMatrix(lookAt);

	//------
	//eye space to clip space conversion matrix - projection matrix
	//------
	//glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, 0.1, 100.0);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	Matrix projectionMat = convertGlmMatrix(projection);
	std::cout << "Projection matrix:" << std::endl;
	printMatrix(projectionMat);

	//-------
	//Final transformation matrix
	//-------
	Matrix finalTransformMat = projectionMat * lookAt;
	std::cout << "Final Transform matrix:" << std::endl;
	printMatrix(finalTransformMat);

	//-------
	//Transform Coordinates
	//--------
	std::vector<Vec> transformedPoints;
	for (Vec& v : allPoints) {
		Vec point4D = create4Dpoint(v);
		Matrix pointMat(4, 1);
		pointMat.copyColumn(1, point4D);
		Matrix transformedP = finalTransformMat * pointMat;
		Vec transformedPnt = transformedP.getColumn(1);
		transformedPoints.push_back(transformedPnt);
	}
	std::cout << " Transformed Points" << std::endl;
	for (Vec transP : transformedPoints) {
		printVector(transP);
	}

	//---------
	//clip space to NDC coordinates
	//---------
	std::vector<Vec> ndcCoordinates;
	for (Vec pt : transformedPoints) {
		Vec perspectiveDividedPnt = perspectiveDivision(pt);
		ndcCoordinates.push_back(perspectiveDividedPnt);
	}

	std::cout << " NDC Points" << std::endl;
	for (Vec p : ndcCoordinates) {
		printVector(p);
	}

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
	//const char* fragmentShaderSourceBlack = getFragmentShaderSource(2);
	//fragmentShader2 = buildAndCompileFragmentShader(fragmentShaderSourceBlack);
	//shaderProgram2 = buildAndLinkShaderProgram(vertexShader, fragmentShader2);

	//----------
	//prepare data to render
	//----------
	RenderObject ro = createRenderObject(ndcCoordinates, triangles);
	

	//--------
	//add data to Render window
	//--------
	w.addRenderObject(ro);
	w.startRenderLoop();

	return 0;
}

Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp) {

	Vec tmp = cameraPosition - targetPoint;
	std::cout << "tmp vector" << std::endl;
	printVector(tmp);
	Vec cameraDirection = tmp.normalize();
	std::cout << "camera direction" << std::endl;
	printVector(cameraDirection);
	Vec tmp2 = tmpLookUp ^ cameraDirection;
	Vec cameraRight = tmp2.normalize();
	std::cout << "camera Right" << std::endl;
	printVector(cameraRight);
	Vec tmp3 = cameraDirection ^ cameraRight;
	Vec cameraUp = tmp3.normalize();
	std::cout << "camera up" << std::endl;
	printVector(cameraUp);

	Matrix cameraCS(4, 4);
	cameraCS.copyRow(1, cameraRight);
	cameraCS.copyRow(2, cameraUp);
	cameraCS.copyRow(3, cameraDirection);
	std::cout << "Camera CS matrix" << std::endl;
	printMatrix(cameraCS);

	Matrix cameraPos(4, 4);
	Vec negCameraPosition = cameraPosition.scale(-1.0);
	cameraPos.copyColumn(4, negCameraPosition);

	std::cout << "Camera neg pos matrix" << std::endl;
	printMatrix(cameraPos);

	Matrix lookAt = cameraCS * cameraPos;
	return lookAt;

}

void printMatrix(Matrix& m) {
	for (int i = 1; i <= m.getNumberOfRows(); i++) {
		for (int j = 1; j <= m.getNumberOfColumns(); j++) {
			std::cout << m.getAt(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printVector(Vec& v) {
	for (int i = 1; i <= v.getSize(); i++) {
		std::cout << v.getElementAt(i) << " ";
	}
	std::cout << std::endl;
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

RenderObject createRenderObject(std::vector<Vec>& points, std::vector<IndexedTriangle>& triangleIndices) {
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

	RenderObject rb(VAO, shaderProgram1, 1, vertexCount);
	return rb;
}

const char* getVertexShaderSource() {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
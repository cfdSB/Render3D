#include "RenderObject.h"
#include <iostream>



RenderObject::RenderObject(GeometryPart * part):part(part)
{
	initializeData();
}

RenderObject::RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount)
	:VAO(VAO), shaderProgram(shaderProgram), drawType(drawType), vertexCount(vertexCount)
{
}


RenderObject::~RenderObject()
{
	/*if (vertexData) {
		delete[] vertexData;
	}*/
	/*if (triangleindexData) {
		delete[] triangleindexData;
	}
	if (normalsData) {
		delete[] normalsData;
	}*/
}

void RenderObject::setShaderProgram(unsigned int shaderProg)
{
	shaderProgram = shaderProg;
}

void RenderObject::setDrawType(int drawType)
{
	this->drawType = drawType;
}

void RenderObject::initializeData()
{
	buildDataArrays();
	createVAO();
}

void RenderObject::buildDataArrays()
{
	
	totalVertexCoordinates = part->getVertices()->size() * coordinatesPerVertex;
	vertexData = new float[totalVertexCoordinates];
	std::cout << "Total point coordinates: " << totalVertexCoordinates << std::endl;

	totalNormalCoordinates = part->getFaceNormals()->size()*coordinatesPerNormal;
	normalsData = new float[totalNormalCoordinates];
	std::cout << "Total normal coordinates: " << totalNormalCoordinates << std::endl;

	totalIndices = part->getTriangles()->size() * 3;
	triangleindexData = new unsigned int[totalIndices];


	int count = 0;
	for (Vec* p : *(part->getVertices())) {
		for (int i = 1; i <= p->getSize(); i++) {
			vertexData[count] = p->getElementAt(i);
			count++;
		}
	}

	count = 0;
	for (Vec* n : *(part->getFaceNormals())) {
		for (int i = 1; i <= n->getSize(); i++) {
			normalsData[count] = n->getElementAt(i);
			count++;
		}
	}

	
	int indexCount = 0;
	for (IndexedTriangle* p : *(part->getTriangles())) {
		for (int i = 0; i < 3; i++) {
			triangleindexData[indexCount] = p->getIndices()[i];
			indexCount++;
		}
	}
}

void RenderObject::createVAO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &indicesEBO);
	glGenBuffers(1, &normalsVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertexCoordinates * sizeof(float), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(unsigned int), triangleindexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, coordinatesPerVertex, GL_FLOAT, GL_FALSE, coordinatesPerVertex * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, totalNormalCoordinates * sizeof(float), normalsData, GL_STATIC_DRAW);

	glVertexAttribPointer(1, coordinatesPerNormal, GL_FLOAT, GL_FALSE, coordinatesPerNormal * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

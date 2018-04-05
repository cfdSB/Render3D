#include "RenderObject.h"
#include <iostream>



RenderObject::RenderObject(DisplayableObject * part):part(part)
{
	initializeData();
}

//RenderObject::RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount)
//	:VAO(VAO), shaderProgram(shaderProgram), drawType(drawType), vertexCount(vertexCount)
//{
//}


RenderObject::~RenderObject()
{
	if (vertexData) {
		delete[] vertexData;
	}
	if (elementIndexData) {
		delete[] elementIndexData;
	}
	if (normalsData) {
		delete[] normalsData;
	}
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
	//buildDataArrays();
	createVAO();
}

void RenderObject::buildDataArrays()
{
	

}

void RenderObject::createVAO()
{
	std::unique_ptr<float[]> vertexData = part->getVertexData();
	std::unique_ptr<unsigned int[]> indicesData = part->getVertexIndexData();
	std::unique_ptr<float[]> normalsData = part->getNormalsData();

	totalVertexCoordinates = part->getVertexCount()*coordinatesPerVertex;
	totalIndices = part->getElementCount()*part->getElementIndexCount();
	totalNormalCoordinates = part->getVertexCount()*coordinatesPerNormal;

	std::cout << "Total vertex corrd: " << totalVertexCoordinates << std::endl;
	std::cout << "Total indices:" << totalIndices << std::endl;
	std::cout << "Total normalCorrd:" << totalNormalCoordinates << std::endl;

	/*for (unsigned int i = 0; i < totalVertexCoordinates; i++) {
		std::cout << "coord: " << vertexData.get()[i] << std::endl;
	}*/

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &indicesEBO);
	glGenBuffers(1, &normalsVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertexCoordinates * sizeof(float), vertexData.get(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(unsigned int), indicesData.get(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, coordinatesPerVertex, GL_FLOAT, GL_FALSE, coordinatesPerVertex * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, totalNormalCoordinates * sizeof(float), normalsData.get(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, coordinatesPerNormal, GL_FLOAT, GL_FALSE, coordinatesPerNormal * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

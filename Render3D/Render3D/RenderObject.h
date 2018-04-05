#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "DisplayableObject.h"
#include <vector>

class RenderObject
{

private:
	DisplayableObject *part;

	unsigned int VAO;
	unsigned int vertexVBO, indicesEBO, normalsVBO;
	unsigned int shaderProgram;
	unsigned int drawType;	//currently int, change to enum or so later
	unsigned int vertexCount; //not used, remove later
	

	float* vertexData = nullptr;
	unsigned int* elementIndexData = nullptr;
	float* normalsData = nullptr;
	unsigned int totalVertexCoordinates, totalNormalCoordinates, totalIndices;

	const int coordinatesPerVertex = 3;
	const int coordinatesPerNormal = 3;
	 
public:
	RenderObject(DisplayableObject *part);
	//RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount);
	virtual ~RenderObject();
	unsigned int getVAO() const { return VAO; };
	unsigned int getShaderProgram() const { return shaderProgram; };
	unsigned int getDrawType() const { return drawType; };
	unsigned int getVertexCount() const { return part->getVertexCount(); };
	void setShaderProgram(unsigned int shaderProg);
	void setDrawType(int drawType);
	const DisplayableObject* getDisplayableObject() { return part; };

private:
	void initializeData();
	void buildDataArrays();
	void createVAO();
};

#endif

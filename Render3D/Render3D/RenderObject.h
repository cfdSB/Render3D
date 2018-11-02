#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "GeometryPart.h"
#include <vector>

class RenderObject
{

private:
	GeometryPart *part;

	unsigned int VAO;
	unsigned int vertexVBO, indicesEBO, normalsVBO, vertexIdVBO;
	unsigned int drawType;	//currently int, change to enum or so later


	const int coordinatesPerVertex = 3;
	const int coordinatesPerNormal = 3;
	 
public:
	RenderObject(GeometryPart *part);
	//RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount);
	virtual ~RenderObject();
	unsigned int getVAO() const { return VAO; };
	unsigned int getDrawType() const { return drawType; };
	unsigned int getVertexCount() const { return part->getVertexCount(); };
	void setDrawType(int drawType);
	const GeometryPart* getDisplayableObject() { return part; };

private:
	void initializeData();
	void buildDataArrays();
	void createVAO();
};

#endif

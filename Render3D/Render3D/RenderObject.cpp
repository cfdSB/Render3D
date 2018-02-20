#include "RenderObject.h"



RenderObject::RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount)
	:VAO(VAO), shaderProgram(shaderProgram), drawType(drawType), vertexCount(vertexCount)
{
}


RenderObject::~RenderObject()
{
}

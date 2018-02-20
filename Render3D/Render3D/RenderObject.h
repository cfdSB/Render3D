#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

class RenderObject
{

private:
	unsigned int VAO;
	unsigned int shaderProgram;
	unsigned int drawType;	//currently int, change to enum or so later
	unsigned int vertexCount;
public:
	RenderObject(unsigned int VAO, unsigned int shaderProgram, unsigned int drawType, unsigned int vertexCount);
	virtual ~RenderObject();
	unsigned int getVAO() const { return VAO; };
	unsigned int getShaderProgram() const { return shaderProgram; };
	unsigned int getDrawType() const { return drawType; };
	unsigned int getVertexCount() const { return vertexCount; };
};

#endif

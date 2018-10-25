#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "ShaderProgram.h"
class ShaderManager
{

private:
	ShaderProgram *objectDisplay, *meshDisplay;
public:
	ShaderManager();
	virtual ~ShaderManager();

	unsigned int getObjectDisplayShaderProgram() { return objectDisplay->getProgramID(); };
	unsigned int getMeshDisplayShaderProgram() { return meshDisplay->getProgramID(); };


private:
	void bootShaderPrograms();
};
#endif


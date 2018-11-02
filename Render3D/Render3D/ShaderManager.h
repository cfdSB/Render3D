#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "ShaderProgram.h"
class ShaderManager
{

private:
	ShaderProgram *objectDisplay, *meshDisplay, *elementSelection;
public:
	ShaderManager();
	virtual ~ShaderManager();

	unsigned int getObjectDisplayShaderProgram() { return objectDisplay->getProgramID(); };
	unsigned int getMeshDisplayShaderProgram() { return meshDisplay->getProgramID(); };
	unsigned int getElementSelectionProgram() { return elementSelection->getProgramID(); };


private:
	void bootShaderPrograms();
};
#endif


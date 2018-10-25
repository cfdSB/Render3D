#include "ShaderManager.h"



ShaderManager::ShaderManager()
{
	objectDisplay = nullptr;
	meshDisplay = nullptr;

	bootShaderPrograms();
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::bootShaderPrograms()
{
	objectDisplay = new ShaderProgram("vShader_transformations_color.vs", "fShader_transformations_color.fs");
}

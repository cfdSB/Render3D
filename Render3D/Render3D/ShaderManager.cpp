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
	meshDisplay = new ShaderProgram("vShader_transformations_meshDisplay.vs", "fShader_transformations_meshDisplay.fs");
	elementSelection = new ShaderProgram("vShader_transformations_selection.vs", "fShader_transformations_selection.fs");
}

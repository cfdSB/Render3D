#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
private:
	unsigned int programID;

public:
	ShaderProgram(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);
	virtual ~ShaderProgram();
	void use();
	unsigned int getProgramID() const { return programID; };

private:
	std::string* readSource(std::string filePath);
	unsigned int compileShader(int shaderType, std::string* source);
	unsigned int linkShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID);
};
#endif


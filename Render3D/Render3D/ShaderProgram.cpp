#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
{
	std::string* vShaderSource = readSource(vertexShaderFilePath);
	std::string* fShaderSource = readSource(fragmentShaderFilePath);
	unsigned int vShader = compileShader(0, vShaderSource);  // 0 for vertex shader
	unsigned int fShader = compileShader(1, fShaderSource);
	programID = linkShaderProgram(vShader, fShader);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

std::string* ShaderProgram::readSource(std::string filePath)
{
	//const char* code = nullptr;
	std::string *codeString = nullptr;
	std::ifstream codeFile;
	std::stringstream sourceStream;

	try {
		codeFile.open(filePath);
		sourceStream << codeFile.rdbuf();
		codeFile.close();
		codeString = new std::string(sourceStream.str());
		//code = codeString.c_str();
		//std::cout << codeString << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
	}
	return codeString;
}

unsigned int ShaderProgram::compileShader(int shaderType, std::string* source)
{
	unsigned int vShader;
	std::string shaderTypeForErrorLog;
	if (shaderType == 0) {
		vShader = glCreateShader(GL_VERTEX_SHADER);
		shaderTypeForErrorLog = "VERTEX";
	}
	else if (shaderType == 1) {
		vShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderTypeForErrorLog = "FRAGMENT";
	}

	const char* source_cstr = source->c_str();
	glShaderSource(vShader, 1, &source_cstr, NULL);
	glCompileShader(vShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderTypeForErrorLog << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return vShader;
}

unsigned int ShaderProgram::linkShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID)
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmentShaderID);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderProgram;
}

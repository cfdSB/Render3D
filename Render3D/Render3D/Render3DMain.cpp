#include "RenderWindow.h"
#include <iostream>

const char* getVertexShaderSource();
const char* getFragmentShaderSource(int);
int buildAndCompileVertexShader(const char* vShaderSource);
int buildAndCompileFragmentShader(const char* fragShaderSource);
int buildAndLinkShaderProgram(int vShader, int fragShader);
void prepRenderData();

int vertexShader, fragmentShader1, fragmentShader2;
int shaderProgram1, shaderProgram2;
unsigned int VAO, VBO, vertexCount;

int main() {
	RenderWindow w;

	//create a renderVAO and pass it to the renderwindow
	//build and compile shader program
	const char* vertexShaderSource = getVertexShaderSource();
	vertexShader = buildAndCompileVertexShader(vertexShaderSource);
	const char* fragmentShaderSource = getFragmentShaderSource(1);
	fragmentShader1 = buildAndCompileFragmentShader(fragmentShaderSource);
	shaderProgram1 = buildAndLinkShaderProgram(vertexShader, fragmentShader1);
	/*const char* fragmentShaderSourceBlack = getFragmentShaderSource(2);
	fragmentShader2 = buildAndCompileFragmentShader(fragmentShaderSourceBlack);
	shaderProgram2 = buildAndLinkShaderProgram(vertexShader, fragmentShader2);*/

	prepRenderData();

	RenderObject rb(VAO, shaderProgram1, 1, vertexCount);
	w.addRenderObject(rb);

	w.startRenderLoop();
	return 0;
}

const char* getVertexShaderSource() {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	return vertexShaderSource;
}

const char* getFragmentShaderSource(int version) {
	const char* fragmentShaderSource = NULL;
	switch (version) {
	case 1: //orange color
		fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		break;
	case 2: //black color
		fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
			"}\n\0";
		break;
	}
	return fragmentShaderSource;
}

int buildAndCompileVertexShader(const char* vShaderSource) {
	int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glCompileShader(vShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return vShader;
}

int buildAndCompileFragmentShader(const char* fragShaderSource) {
	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return fragShader;
}

int buildAndLinkShaderProgram(int vShader, int fragShader) {
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);

	return shaderProgram;
}

void prepRenderData() {

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f,  // top 
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.7f, 0.7f, 0.0f

	};
	vertexCount = 6;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}
//#include "RenderWindow.h"
//#include <iostream>
//#include "Matrix.h"
//#include "Vertex.h"
//#include "Vec.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//
//const char* getVertexShaderSource();
//const char* getFragmentShaderSource(int);
//int buildAndCompileVertexShader(const char* vShaderSource);
//int buildAndCompileFragmentShader(const char* fragShaderSource);
//int buildAndLinkShaderProgram(int vShader, int fragShader);
//void prepRenderData(Matrix& viewTransform, glm::mat4& projectionTransform);
//
//Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp);
//void printMatrix(Matrix& m);
//void printVector(Vec& v);
//Matrix convertGlmMatrix(glm::mat4&);
//
//int vertexShader, fragmentShader1, fragmentShader2;
//int shaderProgram1, shaderProgram2;
//unsigned int VAO, VBO, vertexCount;
//
//
//
//int main() {
//	RenderWindow w;
//
//	Vec cameraPosition(3);
//	cameraPosition.addElement(1, 3.0).addElement(2, -5.0).addElement(3, 1.0);
//
//	Vec targetPoint(3);
//	targetPoint.addElement(1, 3.0).addElement(2, 2.75).addElement(3, 1.0);
//
//	Vec tmpLookUp(3);
//	tmpLookUp.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 1.0);
//
//	Matrix lookAt = computeLookAt(cameraPosition, targetPoint, tmpLookUp);
//	std::cout << "Look At matrix:" << std::endl;
//	printMatrix(lookAt);
//
//	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
//	glm::mat4 projection = glm::ortho(0.0,8.0,0.0,6.0, 0.1, 100.0);
//
//	Matrix projectionMat = convertGlmMatrix(projection);
//	std::cout << "Projection matrix:" << std::endl;
//	printMatrix(projectionMat);
//
//	Matrix finalTransformMatrix = projectionMat * lookAt;
//	std::cout << "Final transform matrix" << std::endl;
//	printMatrix(finalTransformMatrix);
//
//	std::cout << "----------" << std::endl;
//
//	
//	//create a renderVAO and pass it to the renderwindow
//	//build and compile shader program
//	const char* vertexShaderSource = getVertexShaderSource();
//	vertexShader = buildAndCompileVertexShader(vertexShaderSource);
//	const char* fragmentShaderSource = getFragmentShaderSource(1);
//	fragmentShader1 = buildAndCompileFragmentShader(fragmentShaderSource);
//	shaderProgram1 = buildAndLinkShaderProgram(vertexShader, fragmentShader1);
//	//const char* fragmentShaderSourceBlack = getFragmentShaderSource(2);
//	//fragmentShader2 = buildAndCompileFragmentShader(fragmentShaderSourceBlack);
//	//shaderProgram2 = buildAndLinkShaderProgram(vertexShader, fragmentShader2);
//
//	prepRenderData(finalTransformMatrix, projection);
//
//	int rows = 1;
//	int columns = 4;
//	Matrix m(rows, columns);
//	for (int i = 1; i <= 2; i++) {
//		for (int j = 1; j <= 2; j++) {
//			std::cout << m.getAt(i, j)<< " ";
//		}
//	}
//	RenderObject rb(VAO, shaderProgram1, 1, vertexCount);
//	
//	w.addRenderObject(rb);
//	
//	Matrix m1(2,2);
//	m1.setAt(1, 1, 1); m1.setAt(1, 2, 1); m1.setAt(2, 1, 2); m1.setAt(2, 2, 2);
//	Matrix m2(2, 1);
//	m2.setAt(1, 1, 3); /*m2.setAt(1, 2, 3); */ m2.setAt(2, 1, 4); /*m2.setAt(2, 2, 4);*/
//
//	Matrix m3 = m1 * m2;
//	printMatrix(m3);
//	w.startRenderLoop();
//	
//	return 0;
//}
//
//void printMatrix(Matrix& m) {
//	for (int i = 1; i <= m.getNumberOfRows(); i++) {
//		for (int j = 1; j <= m.getNumberOfColumns(); j++) {
//			std::cout << m.getAt(i, j) << " ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//const char* getVertexShaderSource() {
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"uniform mat4 viewTransform;\n"
//		"uniform mat4 projectionTransform;\n"
//		"void main()\n"
//		"{\n"
//		"gl_Position = projectionTransform*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//
//	return vertexShaderSource;
//}
//
//const char* getFragmentShaderSource(int version) {
//	const char* fragmentShaderSource = NULL;
//	switch (version) {
//	case 1: //orange color
//		fragmentShaderSource = "#version 330 core\n"
//			"out vec4 FragColor;\n"
//			"void main()\n"
//			"{\n"
//			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//			"}\n\0";
//		break;
//	case 2: //black color
//		fragmentShaderSource = "#version 330 core\n"
//			"out vec4 FragColor;\n"
//			"void main()\n"
//			"{\n"
//			"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
//			"}\n\0";
//		break;
//	}
//	return fragmentShaderSource;
//}
//
//int buildAndCompileVertexShader(const char* vShaderSource) {
//	int vShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vShader, 1, &vShaderSource, NULL);
//	glCompileShader(vShader);
//
//	// check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//		return -1;
//	}
//
//	return vShader;
//}
//
//int buildAndCompileFragmentShader(const char* fragShaderSource) {
//	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
//	glCompileShader(fragShader);
//
//	// check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		return -1;
//	}
//	return fragShader;
//}
//
//int buildAndLinkShaderProgram(int vShader, int fragShader) {
//	int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vShader);
//	glAttachShader(shaderProgram, fragShader);
//	glLinkProgram(shaderProgram);
//
//	// check for linking errors
//	int success;
//	char infoLog[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader1);
//
//	return shaderProgram;
//}
//
//void prepRenderData(Matrix& viewTransform, glm::mat4& projectionTransform) {
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	//float vertices[] = {
//	//	-0.5f, -0.5f, 0.0f, // left  
//	//	0.5f, -0.5f, 0.0f, // right 
//	//	0.0f,  0.5f, 0.0f,  // top 
//	//	0.5f, -0.5f, 0.0f,
//	//	0.0f, 0.5f, 0.0f,
//	//	0.7f, 0.7f, 0.0f
//
//	//};
//
//	//world coordinates
//	float vertices[] = {
//		2.5, 2.5, 0.0,
//		2.5, 3.5, 0.0,
//		2.5, 2.5, 2.0,
//		2.5, 3.5, 0.0,
//		2.5, 2.5, 2.0,
//		3.5, 2.5, 2.0
//	};
//	vertexCount = 6;
//
//
//
//	/*unsigned int viewTransformLoc = glGetUniformLocation(vertexShader, "viewTransform");
//	glUniformMatrix4fv(viewTransformLoc, 1, GL_TRUE, (const GLfloat*)viewTransform.getDataPtr());*/
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//copy projection matrix
//	glUseProgram(vertexShader);
//	unsigned int projTransformLoc = glGetUniformLocation(vertexShader, "projectionTransform");
//	glUniformMatrix4fv(projTransformLoc, 1, GL_TRUE, viewTransform.getDataPtr());
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//}
//
//std::vector<Vertex> getVerticesInWorldCS() {
//	std::vector<Vertex> vertices;
//	Vertex v1(2.5, 2.5, 0); Vertex v2(3.5, 2.5, 0); Vertex v3(3.5, 3.0, 0); Vertex v4(2.5, 3.0, 0.0);
//	Vertex v5(2.5, 2.5, 2.0); Vertex v6(3.5, 2.5, 2.0); Vertex v7(3.5, 3.0, 2.0); Vertex v8(2.5, 3.0, 2.0);
//
//	vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
//	vertices.push_back(v5); vertices.push_back(v6); vertices.push_back(v7); vertices.push_back(v8);
//
//	return vertices;
//}
//
//Matrix computeLookAt(Vec& cameraPosition, Vec& targetPoint, Vec& tmpLookUp) {
//
//	Vec tmp = cameraPosition - targetPoint;
//	std::cout << "tmp vector" << std::endl;
//	printVector(tmp);
//	Vec cameraDirection = tmp.normalize();
//	std::cout << "camera direction" << std::endl;
//	printVector(cameraDirection);
//	Vec tmp2 = tmpLookUp ^ cameraDirection;
//	Vec cameraRight = tmp2.normalize();
//	std::cout << "camera Right" << std::endl;
//	printVector(cameraRight);
//	Vec tmp3 = cameraDirection ^ cameraRight;
//	Vec cameraUp = tmp3.normalize();
//	std::cout << "camera up" << std::endl;
//	printVector(cameraUp);
//
//	Matrix cameraCS(4, 4);
//	cameraCS.copyRow(1, cameraRight);
//	cameraCS.copyRow(2, cameraUp);
//	cameraCS.copyRow(3, cameraDirection);
//	std::cout << "Camera CS matrix" << std::endl;
//	printMatrix(cameraCS);
//
//	Matrix cameraPos(4, 4);
//	Vec negCameraPosition = cameraPosition.scale(-1.0);
//	cameraPos.copyColumn(4, negCameraPosition);
//
//	std::cout<<"Camera neg pos matrix" << std::endl;
//	printMatrix(cameraPos);
//
//	Matrix lookAt = cameraCS * cameraPos;
//	return lookAt;
//	
//}
//
//void printVector(Vec& v) {
//	for (int i = 1; i <= v.getSize(); i++) {
//		std::cout << v.getElementAt(i) << " ";
//	}
//	std::cout << std::endl;
//}
//
//Matrix convertGlmMatrix(glm::mat4& m) {
//	Matrix convert(4, 4);
//
//	for (int i = 1; i <= 4; i++) {
//		glm::vec4 vect = glm::vec4(m[i - 1]);
//		Vec v(4);
//		for (int j = 1; j <= 4; j++) {
//			v.addElement(j, vect[j - 1]);
//		}
//		convert.copyColumn(i, v);
//	}
//
//	return convert;
//}
int test() {
	return 0;
}
#include "RenderWindow.h"
#include <iostream>



void RenderWindow::initGLFW()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

RenderWindow::RenderWindow()
{
	initGLFW();
	window = createGLFWWindow();
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetWindowUserPointer(window, window);
	initGladLoader();
	
}


RenderWindow::~RenderWindow()
{
	glfwTerminate();
}

GLFWwindow* RenderWindow::createGLFWWindow() {
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	return window;
}

void RenderWindow::initGladLoader() {
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}
}

void RenderWindow::startRenderLoop() {

	while (!glfwWindowShouldClose(window)) {

		//check if window close is triggerred
		processInput(window);

		//render something
		render();

		//----------------

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void RenderWindow::addRenderObject(RenderObject & obj)
{
	renderObjects.push_back(obj);
}

void RenderWindow::setViewParameters(Vec position, Vec targetPoint)
{
	view.setViewParameters(position, targetPoint);
}

void RenderWindow::updateLookAtMatrix(Matrix lookAt)
{
	
}


void RenderWindow::render() {
	//render background
	//----------------
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//----------
	//loop through VAOs and draw 
	//----------
	for (RenderObject& rb : renderObjects) {
		glBindVertexArray(rb.getVAO()); 
		GLenum drawType;
		if (rb.getDrawType() == 1) {
			drawType = GL_TRIANGLES;
		}
		glUseProgram(rb.getShaderProgram());
		unsigned int uniformLocationView = glGetUniformLocation(rb.getShaderProgram(), "viewMat");
		
		glUniformMatrix4fv(uniformLocationView, 1, GL_TRUE, view.getLookAtMatrix().getDataPtr());

		glDrawElements(drawType, rb.getVertexCount(), GL_UNSIGNED_INT, 0);
	}

}

void RenderWindow::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Vec newCameraPosition = view.getCameraPosition() - view.getCameraDirection();
		this->setViewParameters(newCameraPosition, view.getCameraTarget());
	}else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		Vec newCameraPosition = view.getCameraPosition() + view.getCameraDirection();
		this->setViewParameters(newCameraPosition, view.getCameraTarget());
	}else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Vec newCameraPosition = view.getCameraPosition() - view.getCameraRight();
		this->setViewParameters(newCameraPosition, view.getCameraTarget());
	}else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Vec newCameraPosition = view.getCameraPosition() + view.getCameraRight();
		this->setViewParameters(newCameraPosition, view.getCameraTarget());
	}
}




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
	glfwSetKeyCallback(window, key_callback);
	//glfwSetWindowUserPointer(window, window);
	initGladLoader();
	configureGlobalOpenglState();
	
}


RenderWindow::~RenderWindow()
{
	glfwTerminate();
}

GLFWwindow* RenderWindow::createGLFWWindow() {
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Render3D", NULL, NULL);
	
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
		//glfwPollEvents();
		glfwWaitEvents(); //sleeps the thread and waits for event to occur
	}
}

void RenderWindow::addRenderObject(RenderObject* obj)
{
	renderObjects.push_back(obj);
}

void RenderWindow::setViewParameters(Vec position, Vec targetPoint)
{
	view.setViewParameters(position, targetPoint);
}

void RenderWindow::setProjectionParameters(float projectionAngle, unsigned int scrWidth, unsigned int scrHeight)
{
	view.setProjectionParameters(projectionAngle, scrWidth, scrHeight);
}

void RenderWindow::updateLookAtMatrix(Matrix lookAt)
{
	
}

const BoundingBox* RenderWindow::getWindowObjectsBoundingBox()
{
	return renderObjects.at(0)->getDisplayableObject()->getBoundingBox();
}


void RenderWindow::render() {
	//render background
	//----------------
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	//----------
	//loop through VAOs and draw 
	//----------
	for (RenderObject* rb : renderObjects) {

		glUseProgram(rb->getShaderProgram());
		unsigned int uniformLocationView = glGetUniformLocation(rb->getShaderProgram(), "viewMat");
		unsigned int uniformLightLocation = glGetUniformLocation(rb->getShaderProgram(), "lightPos");
		unsigned int uniformLocationProj = glGetUniformLocation(rb->getShaderProgram(), "projectionMat");
		unsigned int uniformObjectColor = glGetUniformLocation(rb->getShaderProgram(), "objectColor");
		unsigned int isMeshDisplay = glGetUniformLocation(rb->getShaderProgram(), "isMeshDisplay");

		glBindVertexArray(rb->getVAO());
		GLenum drawType;
		if (rb->getDrawType() == 1) {
			drawType = GL_TRIANGLES;
		}
		else if (rb->getDrawType() == 2) {
			drawType = GL_LINES;
		}
		//define object color
		Vec objectColor(3);
		objectColor.addElement(1, 0.0).addElement(2, 1.0).addElement(3, 0.0);
		
		// GL_TRUE is used below which makes transpose of a matrix before sending to shader.
		//This is done because Render3D uses row-major way of storing the matrix numbers, but
		//openGL is expecting column-major. So first row of Render3D matrix becomes 1st column
		//of openGL matrix. Hence, we transpose the matrix to bring it to the correct form in
		//openGL

		glUniformMatrix4fv(uniformLocationView, 1, GL_TRUE, view.getLookAtMatrix().getDataPtr());
		glUniformMatrix4fv(uniformLocationProj, 1, GL_TRUE, view.getProjectionMatrix().getDataPtr());
		glUniform3fv(uniformLightLocation, 1, view.getCameraPosition().getDataPtr());
		glUniform3fv(uniformObjectColor, 1, objectColor.getDataPtr());
		glUniform1i(isMeshDisplay, 0);	//0 for false

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(drawType, rb->getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisable(GL_POLYGON_OFFSET_FILL);

		//display mesh 
		if (isMeshDisplayed == true) {

			GLenum drawType = GL_TRIANGLES;
			Vec meshColor(3);
			meshColor.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);

			glUniform3fv(uniformObjectColor, 1, meshColor.getDataPtr());
			glUniform1i(isMeshDisplay, 1);	//0 for false

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(drawType, rb->getVertexCount(), GL_UNSIGNED_INT, 0);
		}

		
	}

	
}

void RenderWindow::configureGlobalOpenglState()
{
	glEnable(GL_DEPTH_TEST);
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




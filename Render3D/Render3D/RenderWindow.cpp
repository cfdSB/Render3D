#include "RenderWindow.h"
#include <iostream>
#include "DebugUtilities.h"



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

	createSelectionBuffer();
	
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

void RenderWindow::createSelectionBuffer()
{
	selectionBuffer = new TextureFrameBuffer(view.getScreenWidth(), view.getScreenHeight());

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

void RenderWindow::updateProjectionWindowSize()
{
	if (view.getProjectionType() == View::PROJECTION_TYPE::Parallel) {
		const BoundingBox *box = getWindowObjectsBoundingBox();
		Point3D lowerLeftCorner = box->getLowerLeftCorner();
		Point3D upperRightCorner = box->getUpperRightCorner();
		Point3D corner3(lowerLeftCorner.getCoordinates()->getElementAt(1),
			upperRightCorner.getCoordinates()->getElementAt(2),
			upperRightCorner.getCoordinates()->getElementAt(3));
		
		Point3D corner4(upperRightCorner.getCoordinates()->getElementAt(1),
			lowerLeftCorner.getCoordinates()->getElementAt(2),
			lowerLeftCorner.getCoordinates()->getElementAt(3));

		Matrix pointsHolder(4, 4);
		const Vec* lowerLeftCornerVector = lowerLeftCorner.getCoordinates();
		const Vec* upperRightCornerVector = upperRightCorner.getCoordinates();
		const Vec* corner3Vector = corner3.getCoordinates();
		const Vec* corner4Vector = corner4.getCoordinates();

		pointsHolder.copyColumn(1, *lowerLeftCornerVector);
		pointsHolder.copyColumn(2, *upperRightCornerVector);
		pointsHolder.copyColumn(3, *corner3Vector);
		pointsHolder.copyColumn(4, *corner4Vector);

		pointsHolder.setAt(4, 1, 1.0);
		pointsHolder.setAt(4, 2, 1.0);
		pointsHolder.setAt(4, 3, 1.0);
		pointsHolder.setAt(4, 4, 1.0);
	
		//std::cout << "Points matrix" << std::endl;
		//DebugUtilities::printMatrix(pointsHolder);

		//transform to eye space
		Matrix transformedPoints = view.getLookAtMatrix()*pointsHolder;

		//std::cout << "eye space transformed bounding box matrix" << std::endl;
		//DebugUtilities::printMatrix(transformedPoints);

		//find min max coordinates in each direction

		float left = findMin(transformedPoints.getAt(1, 1), transformedPoints.getAt(1, 2), transformedPoints.getAt(1, 3), transformedPoints.getAt(1, 4));
		float right = findMax(transformedPoints.getAt(1, 1), transformedPoints.getAt(1, 2), transformedPoints.getAt(1, 3), transformedPoints.getAt(1, 4));

		float bottom = findMin(transformedPoints.getAt(2, 1), transformedPoints.getAt(2, 2), transformedPoints.getAt(2, 3), transformedPoints.getAt(2, 4));
		float top = findMax(transformedPoints.getAt(2, 1), transformedPoints.getAt(2, 2), transformedPoints.getAt(2, 3), transformedPoints.getAt(2, 4));

		float requiredAspectRatio = (float)(view.getScreenWidth() / view.getScreenHeight());
		float steps = (right - left) / requiredAspectRatio + 1;

		float correctedRight = left + steps * requiredAspectRatio;
		float correctedTop = bottom + steps * 1.0; //for each aspect ratio amount increase in x, increase 1 in y

		float correctionRight = correctedRight - right;
		float correctionTop = correctedTop - top;

		float correctedLeft = left - correctionRight / 2.0;
		correctedRight = correctedRight - correctionRight / 2.0;

		float correctedBottom = bottom - correctionTop / 2.0;
		correctedTop = correctedTop - correctionTop / 2.0;

		float nearby = -1.0 * findMin(transformedPoints.getAt(3, 1), transformedPoints.getAt(3, 2), transformedPoints.getAt(3, 3), transformedPoints.getAt(3, 4));
		float faraway = -1.0 * findMax(transformedPoints.getAt(3, 1), transformedPoints.getAt(3, 2), transformedPoints.getAt(3, 3), transformedPoints.getAt(3, 4));

		std::cout << "viewing volume: " << correctedLeft << ", " << correctedRight << ", " << correctedBottom << ", " << correctedTop << ", " << nearby << ", " << faraway << std::endl;
		view.setProjectionWindowSize(correctedLeft, correctedRight, correctedBottom, correctedTop, 0.1, 1.0e5);
	}
}

const BoundingBox* RenderWindow::getWindowObjectsBoundingBox() const
{
	return renderObjects.at(0)->getDisplayableObject()->getBoundingBox();
}

void RenderWindow::setProjectionWindowParameters(float left, float right, float bottom, float top, float nearby, float faraway)
{
	view.setProjectionWindowSize(left, right, bottom, top, nearby, faraway);
}

unsigned int RenderWindow::getFaceIDAtLocation(unsigned int xPos, unsigned int yPos)
{
	TextureFrameBuffer::PixelInfo info = selectionBuffer->readPixel(xPos, yPos);
	return static_cast<unsigned int> (info.f1);
}


void RenderWindow::render() {

	//-------------------------
	//get transformation matrix
	//-------------------------
	Matrix mvp = view.getMVPMatrix();


	//----------------------
	//first render on the texture buffer for element IDs. It doesn't affect the visual display
	//----------------------
	glBindFramebuffer(GL_FRAMEBUFFER, selectionBuffer->getFBO());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	unsigned int elementSelectionShaderProgram = shaderManager->getElementSelectionProgram();
	glUseProgram(elementSelectionShaderProgram);
	unsigned int uniformLocationMvpMatSelection = glGetUniformLocation(elementSelectionShaderProgram, "mvpMat");
	glUniformMatrix4fv(uniformLocationMvpMatSelection, 1, GL_TRUE, mvp.getDataPtr());

	for (RenderObject* rb : renderObjects) {
		
		glBindVertexArray(rb->getVAO());
		GLenum drawType = GL_TRIANGLES;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(drawType, rb->getVertexCount(), GL_UNSIGNED_INT, 0);
	}

	//bind the default buffer back
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//--------------------------------
	//render on the default (display) buffer
	//----------------
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	//----------
	//loop through VAOs and draw 
	//----------
	for (RenderObject* rb : renderObjects) {
		unsigned int objectDisplayShaderProgram = shaderManager->getObjectDisplayShaderProgram();
		glUseProgram(objectDisplayShaderProgram);
		unsigned int uniformLightLocation = glGetUniformLocation(objectDisplayShaderProgram, "lightPos");
		unsigned int uniformLocationMvpMat = glGetUniformLocation(objectDisplayShaderProgram, "mvpMat");
		unsigned int uniformObjectColor = glGetUniformLocation(objectDisplayShaderProgram, "objectColor");

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

		glUniformMatrix4fv(uniformLocationMvpMat, 1, GL_TRUE, mvp.getDataPtr());
		glUniform3fv(uniformLightLocation, 1, view.getCameraPosition().getDataPtr());
		glUniform3fv(uniformObjectColor, 1, objectColor.getDataPtr());

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(drawType, rb->getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisable(GL_POLYGON_OFFSET_FILL);

		//display mesh 
		if (isMeshDisplayed == true) {

			unsigned int meshDisplayShaderProgram = shaderManager->getMeshDisplayShaderProgram();
			glUseProgram(meshDisplayShaderProgram);
			unsigned int uniformLocationMvpMesh = glGetUniformLocation(meshDisplayShaderProgram, "mvpMat");
			unsigned int uniformObjectColorMesh = glGetUniformLocation(meshDisplayShaderProgram, "objectColor");

			glBindVertexArray(rb->getVAO());

			GLenum drawType = GL_TRIANGLES;

			Vec meshColor(3);
			meshColor.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0); //black

			glUniform3fv(uniformObjectColorMesh, 1, meshColor.getDataPtr());
			glUniformMatrix4fv(uniformLocationMvpMesh, 1, GL_TRUE, mvp.getDataPtr());

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(drawType, rb->getVertexCount(), GL_UNSIGNED_INT, 0);
		}

		
	}

	
}

void RenderWindow::configureGlobalOpenglState()
{
	glEnable(GL_DEPTH_TEST);
}

float RenderWindow::findMin(float p1, float p2, float p3, float p4)
{
	float min1 = std::min(p1, p2);
	float min2 = std::min(p3, p4);
	float min = std::min(min1, min2);

	return min;
}

float RenderWindow::findMax(float p1, float p2, float p3, float p4)
{
	float max1 = std::max(p1, p2);
	float max2 = std::max(p3, p4);
	float max = std::max(max1, max2);

	return max;
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




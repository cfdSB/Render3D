#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "RenderObject.h"
#include "View.h"
#include "Matrix.h"
#include "RenderWindowEventManager.h"
#include <algorithm>
#include "GeometryUtility.h"
#include "ShaderManager.h"
#include "TextureFrameBuffer.h"

class RenderWindow
{
private:
	GLFWwindow *window;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	std::vector<RenderObject*> renderObjects;
	View view;
	TextureFrameBuffer *selectionBuffer;

	struct MousePositionData {
		double xPos=0.0, yPos = 0.0;
	};

	MousePositionData pos;

	bool isMeshDisplayed = false;
	bool mouseInDragMode = false;

	ShaderManager *shaderManager = nullptr;

private:
	void initGLFW();
	void processInput(GLFWwindow *window);
	GLFWwindow* createGLFWWindow();
	void createSelectionBuffer();
	void initGladLoader();
	void render();
	void configureGlobalOpenglState();

	float findMin(float p1, float p2, float p3, float p4);
	float findMax(float p1, float p2, float p3, float p4);

public:
	RenderWindow();
	virtual ~RenderWindow();
	void startRenderLoop();
	void addRenderObject(RenderObject* obj);
	void setViewParameters(Vec position, Vec targetPoint);
	void setProjectionParameters(float projectionAngle, unsigned int scrWidth, unsigned int scrHeight);
	void updateProjectionWindowSize();
	const View& getView() const { return view; };
	double getMouseXposition() { return pos.xPos; };
	double getMouseYposition() { return pos.yPos; };
	void setMouseXposition(double x) { pos.xPos = x; };
	void setMouseYposition(double y) { pos.yPos = y; };
	bool isMouseInDragMode() const { return mouseInDragMode; };
	void setMouseInDragMode(bool mode) { this->mouseInDragMode = mode; };
	const BoundingBox* getWindowObjectsBoundingBox() const;
	void setMeshDisplayed(bool status) { isMeshDisplayed = status; };
	bool getMeshDisplayed() const { return isMeshDisplayed; };
	void setViewProjectionType(View::PROJECTION_TYPE type) { view.setProjectionType(type); };
	void setProjectionWindowParameters(float left, float right, float bottom, float top, float nearby, float faraway);
	const std::vector<RenderObject*>& getRenderObjects() const { return renderObjects; };
	void setShaderManager(ShaderManager* manager) { shaderManager = manager; };
	unsigned int getFaceIDAtLocation(unsigned int xPos, unsigned int yPos);
};



#endif


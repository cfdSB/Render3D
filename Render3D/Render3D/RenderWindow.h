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

class RenderWindow
{
private:
	GLFWwindow *window;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	std::vector<RenderObject*> renderObjects;
	View view;

	struct MousePositionData {
		double xPos=0.0, yPos = 0.0;
	};

	MousePositionData pos;

	bool isMeshDisplayed = false;

private:
	void initGLFW();
	void processInput(GLFWwindow *window);
	GLFWwindow* createGLFWWindow();
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
	const View& getView() { return view; };
	double getMouseXposition() { return pos.xPos; };
	double getMouseYposition() { return pos.yPos; };
	void setMouseXposition(double x) { pos.xPos = x; };
	void setMouseYposition(double y) { pos.yPos = y; };
	const BoundingBox* getWindowObjectsBoundingBox();
	void setMeshDisplayed(bool status) { isMeshDisplayed = status; };
	bool getMeshDisplayed() const { return isMeshDisplayed; };
	void setViewProjectionType(View::PROJECTION_TYPE type) { view.setProjectionType(type); };
};



#endif


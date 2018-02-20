#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "RenderObject.h"

class RenderWindow
{
private:
	GLFWwindow *window;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	std::vector<RenderObject> renderObjects;

private:
	void initGLFW();
	void processInput(GLFWwindow *window);
	GLFWwindow* createGLFWWindow();
	void initGladLoader();
	void render();

public:
	RenderWindow();
	virtual ~RenderWindow();
	void startRenderLoop();
	void addRenderObject(RenderObject& obj);
	
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif


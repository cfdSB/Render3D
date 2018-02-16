#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderWindow
{
private:
	GLFWwindow *window;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

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
	
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

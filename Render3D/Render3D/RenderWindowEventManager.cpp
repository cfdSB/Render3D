#include "RenderWindowEventManager.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset)
{
	RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));
	if (!window) {
		std::cout << "Error while getting window pointer" << std::endl;
		return;
	}
	View view = window->getView();
	Vec newDirection = Vec(view.getCameraDirection());
	Vec newCameraPosition = view.getCameraPosition() + newDirection.scale(yoffset);
	window->setViewParameters(newCameraPosition, view.getCameraTarget());
}
#include "RenderWindowEventManager.h"
#include <iostream>

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

void cursor_position_callback(GLFWwindow * wnd, double xPos, double yPos)
{
	if (glfwGetMouseButton(wnd, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));

		double oldXpos = window->getMouseXposition();
		double oldYpos = window->getMouseYposition();
		std::cout << "old position: " << oldXpos << " " << oldYpos << std::endl;
		std::cout << "New position: " << xPos << " " << yPos << std::endl;

		window->setMouseXposition(xPos);
		window->setMouseYposition(yPos);

		double xDiff = xPos - oldXpos;

		Vec distance = window->getView().getCameraPosition() - window->getView().getCameraTarget();
		double dist = sqrt(pow(distance.getElementAt(1), 2) + pow(distance.getElementAt(2), 2) + pow(distance.getElementAt(3), 2)) -0.1;
		double scale = (tan(0.785398/2.0)*dist*2.0 + tan(0.785398/2.0)*0.1*2.0)/800.0; 
		double positionChange = xDiff * scale;
		Vec newCameraPosition = window->getView().getCameraPosition() - window->getView().getCameraRight().scale(positionChange);
		Vec newCameraTarget = window->getView().getCameraTarget() - window->getView().getCameraRight().scale(positionChange);
		window->setViewParameters(newCameraPosition, newCameraTarget);
	}

}

void mouse_button_callback(GLFWwindow * wnd, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));
		double xpos, ypos;
		glfwGetCursorPos(wnd, &xpos, &ypos);
		window->setMouseXposition(xpos);
		window->setMouseYposition(ypos);
	}
}

#include "RenderWindowEventManager.h"
#include <iostream>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.

	int iconified = glfwGetWindowAttrib(window, GLFW_ICONIFIED);
	
	if (!iconified) { // when iconified (window minimized), it makes size 0,0 which creates problems for glm proj matrix calc 
		glViewport(0, 0, width, height);
		RenderWindow *wnd = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
		wnd->setProjectionParameters(45.0, width, height);
	}
}

void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset)
{
	RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));
	if (!window) {
		std::cout << "Error while getting window pointer" << std::endl;
		return;
	}
	const BoundingBox *box = window->getWindowObjectsBoundingBox();
	float partRange = findDistance(box->getLowerLeftCorner(), box->getUpperRightCorner());
	float scale = (partRange / 20.0)*yoffset;
	View view = window->getView();
	Vec newDirection = Vec(view.getCameraDirection());
	Vec newCameraPosition = view.getCameraPosition() + newDirection.scale(scale);
	window->setViewParameters(newCameraPosition, view.getCameraTarget());
}

void cursor_position_callback(GLFWwindow * wnd, double xPos, double yPos)
{
	if (glfwGetMouseButton(wnd, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		
		double positionXChange, positionYChange;
		calculatePositionChange(wnd, xPos, yPos, &positionXChange, &positionYChange);
		RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));

		Vec newCameraPosition = window->getView().getCameraPosition() - window->getView().getCameraRight().scale(positionXChange);
		newCameraPosition = newCameraPosition + window->getView().getCameraUp().scale(positionYChange);
		Vec newCameraTarget = window->getView().getCameraTarget() - window->getView().getCameraRight().scale(positionXChange);
		newCameraTarget = newCameraTarget + window->getView().getCameraUp().scale(positionYChange);
		window->setViewParameters(newCameraPosition, newCameraTarget);

	}else if (glfwGetMouseButton(wnd, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		double positionXChange, positionYChange;
		calculatePositionChange(wnd, xPos, yPos, &positionXChange, &positionYChange);
		RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));

		Vec newCameraPosition = window->getView().getCameraPosition() - window->getView().getCameraRight().scale(positionXChange);
		newCameraPosition = newCameraPosition + window->getView().getCameraUp().scale(positionYChange);
		Vec newCameraTarget = window->getView().getCameraTarget();
		window->setViewParameters(newCameraPosition, newCameraTarget);
	}

}

void mouse_button_callback(GLFWwindow * wnd, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS) {
		RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));
		double xpos, ypos;
		glfwGetCursorPos(wnd, &xpos, &ypos);
		window->setMouseXposition(xpos);
		window->setMouseYposition(ypos);
	}
}

void calculatePositionChange(GLFWwindow* wnd, double xPos, double yPos, double* xPosChange, double* yPosChange) {
	
	RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));
	double oldXpos = window->getMouseXposition();
	double oldYpos = window->getMouseYposition();
	//std::cout << "old position: " << oldXpos << " " << oldYpos << std::endl;
	//std::cout << "New position: " << xPos << " " << yPos << std::endl;

	window->setMouseXposition(xPos);
	window->setMouseYposition(yPos);

	double xDiff = xPos - oldXpos;
	double yDiff = yPos - oldYpos;

	Vec distance = window->getView().getCameraPosition() - window->getView().getCameraTarget();
	double dist = sqrt(pow(distance.getElementAt(1), 2) + pow(distance.getElementAt(2), 2) + pow(distance.getElementAt(3), 2)) - 0.1;
	double distTmp = (tan(0.785398 / 2.0)*dist*2.0 + tan(0.785398 / 2.0)*0.1*2.0);
	double xScale = distTmp / 800.0;
	double yScale = distTmp / 600.0;
	*xPosChange = xDiff * xScale;
	*yPosChange = yDiff * yScale;
}

void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		if (glfwGetKey(wnd, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));
			const BoundingBox *box = window->getWindowObjectsBoundingBox();
			float zoomOffScale = findZoomOffDistance(box);
			std::cout << "camera zoomOff distance: " << zoomOffScale << std::endl;
			Vec direction = Vec(window->getView().getCameraDirection());
			Vec targetPoint = box->getCenterPoint();
			Vec zoomOffCameraPosition = direction.scale(zoomOffScale) + targetPoint;
			window->setViewParameters(zoomOffCameraPosition, targetPoint);
		}
	}
	
}

float findZoomOffDistance(const BoundingBox *box)
{
	float farthestPoint = findDistance(box->getLowerLeftCorner(), box->getCenterPoint());
	std::cout << "farthest point distance: " << farthestPoint << std::endl;

	float perspectiveAngle = 45.0; //in degrees
	float PI = 3.14159265;
	float positionScale = farthestPoint / tan(perspectiveAngle / 2.0*PI / 180.0);

	return positionScale;
}

float findDistance(const Vec& point1, const Vec& point2) {

	float xDiff = point1.getElementAt(1) - point2.getElementAt(1);
	float yDiff = point1.getElementAt(2) - point2.getElementAt(2);
	float zDiff = point1.getElementAt(3) - point2.getElementAt(3);
	float dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));
	
	return dist;
}

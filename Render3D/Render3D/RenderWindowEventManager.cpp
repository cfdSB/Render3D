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
		
		Vec currentWindowSize = wnd->getView().getProjectionWindowSize();
		double screenWidth = (double)wnd->getView().getScreenWidth();
		double screenHeight = (double)wnd->getView().getScreenHeight();
		double viewVolWidth = currentWindowSize.getElementAt(2) - currentWindowSize.getElementAt(1);
		double viewVolHeight = currentWindowSize.getElementAt(4) - currentWindowSize.getElementAt(3);

		double widthChange, heightChange;
		if (screenWidth >= screenHeight) {
			float aspectRatio = (float)screenWidth / (float)screenHeight;
			double newVolHeight = viewVolWidth / aspectRatio;
			heightChange = newVolHeight - viewVolHeight;
			widthChange = 0.0;
		}
		else {
			float aspectRatio = (float)screenHeight / (float)screenWidth;
			double newWidth = viewVolHeight / aspectRatio;
			widthChange = newWidth - viewVolWidth;
			heightChange = 0.0;
		}

		double newLeft = currentWindowSize.getElementAt(1) - widthChange / 2.0;
		double newRight = currentWindowSize.getElementAt(2) + widthChange / 2.0;
		double newBottom = currentWindowSize.getElementAt(3) - heightChange / 2.0;
		double newTop = currentWindowSize.getElementAt(4) + heightChange / 2.0;
		double newNear = currentWindowSize.getElementAt(5);
		double newFar = currentWindowSize.getElementAt(6);

		//float screenAspectRatio = (float)screenWidth / (float)screenHeight;
		//float viewingVolAspectRatio = (newRight - newLeft) / (newTop - newBottom);
		//std::cout << "Screen aspect ratio: " << screenAspectRatio << std::endl;
		//std::cout << "View Vol aspect ratio: " << viewingVolAspectRatio << std::endl;

		wnd->setProjectionWindowParameters(newLeft, newRight, newBottom, newTop, newNear, newFar);


	}
}

void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset)
{
	RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));
	if (!window) {
		std::cout << "Error while getting window pointer" << std::endl;
		return;
	}
	
	if (window->getView().getProjectionType() == View::PROJECTION_TYPE::Perpective) {
		const BoundingBox *box = window->getWindowObjectsBoundingBox();
		float partRange = GeometryUtility::findDistance(box->getLowerLeftCorner(), box->getUpperRightCorner());
		float scale = (partRange / 20.0)*yoffset;
		View view = window->getView();
		Vec newDirection = Vec(view.getCameraDirection());
		Vec newCameraPosition = view.getCameraPosition() + newDirection.scale(scale);
		window->setViewParameters(newCameraPosition, view.getCameraTarget());
	}
	else {

		Vec currentWindowSize = window->getView().getProjectionWindowSize();
		double screenWidth = (double)window->getView().getScreenWidth();
		double screenHeight = (double)window->getView().getScreenHeight();
		double viewVolWidth = currentWindowSize.getElementAt(2) - currentWindowSize.getElementAt(1);
		double viewVolHeight = currentWindowSize.getElementAt(4) - currentWindowSize.getElementAt(3);


		double widthChange, heightChange;
		double percentChange = 2 * yoffset;

		if (screenWidth >= screenHeight) {
			widthChange = viewVolWidth*percentChange / 100.00;
			double newWidth = viewVolWidth + widthChange;
			double newHeight = newWidth / (screenWidth / screenHeight);
			heightChange = newHeight - viewVolHeight;
		}
		else {
			heightChange = viewVolHeight * percentChange / 100.00;
			double newHeight = viewVolHeight + heightChange;
			double newWidth = newHeight / (screenHeight / screenWidth);
			widthChange = newWidth - viewVolWidth;
		}
		
		double newLeft = currentWindowSize.getElementAt(1) - widthChange / 2.0;
		double newRight = currentWindowSize.getElementAt(2) + widthChange / 2.0;
		double newBottom = currentWindowSize.getElementAt(3) - heightChange / 2.0;
		double newTop = currentWindowSize.getElementAt(4) + heightChange / 2.0;
		double newNear = currentWindowSize.getElementAt(5);
		double newFar = currentWindowSize.getElementAt(6);

		window->setProjectionWindowParameters(newLeft, newRight, newBottom, newTop, newNear, newFar);

		//float screenAspectRatio = (float)screenWidth / (float)screenHeight;
		//float viewingVolAspectRatio = (newRight - newLeft) / (newTop - newBottom);
		//std::cout << "Screen aspect ratio: " << screenAspectRatio << std::endl;
		//std::cout << "View Vol aspect ratio: " << viewingVolAspectRatio << std::endl;
	}
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
		window->setMouseInDragMode(true);

		Vec newCameraPosition = window->getView().getCameraPosition() - window->getView().getCameraRight().scale(positionXChange);
		newCameraPosition = newCameraPosition + window->getView().getCameraUp().scale(positionYChange);
		Vec newCameraTarget = window->getView().getCameraTarget();
		window->setViewParameters(newCameraPosition, newCameraTarget);

		//compute new projection parameters for parallel projection
		/*if (window->getView().getProjectionType() == View::PROJECTION_TYPE::Parallel) {
			float volume[6];
			calculateViewingVolume(window, volume);
			window->setProjectionWindowParameters(volume[0], volume[1], volume[2], volume[3], volume[4], volume[5]);
		}*/ //NO NEED
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
	else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		RenderWindow *window = static_cast<RenderWindow*>(glfwGetWindowUserPointer(wnd));

		if (!window->isMouseInDragMode()) {
			double xpos, ypos;
			glfwGetCursorPos(wnd, &xpos, &ypos);
			std::cout << "Mouse clicked at " << xpos << ", " << ypos << std::endl;
			//computeClickLocation(window, xpos, ypos);
			findClickedFaceID(window, (unsigned int)xpos, (unsigned int)ypos);
		}
		else {
			window->setMouseInDragMode(false);
		}
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

			Vec direction = Vec(window->getView().getCameraDirection());
			Vec targetPoint = *(box->getCenterPoint().getCoordinates());
			Vec zoomOffCameraPosition = direction.scale(zoomOffScale) + targetPoint;

			window->setViewParameters(zoomOffCameraPosition, targetPoint);

			//compute new projection parameters for parallel projection
			if (window->getView().getProjectionType() == View::PROJECTION_TYPE::Parallel) {
				float volume[6];
				calculateViewingVolume(window, volume);
				window->setProjectionWindowParameters(volume[0], volume[1], volume[2], volume[3], volume[4], volume[5]);
			}
			

		}
	}
	else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		if (glfwGetKey(wnd, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));
			window->setMeshDisplayed(!window->getMeshDisplayed());
		}
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if (glfwGetKey(wnd, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			RenderWindow *window = static_cast<RenderWindow*> (glfwGetWindowUserPointer(wnd));
			if (window->getView().getProjectionType() == View::PROJECTION_TYPE::Parallel) {
				window->setViewProjectionType(View::PROJECTION_TYPE::Perpective);
			}
			else {
				window->setViewProjectionType(View::PROJECTION_TYPE::Parallel);
			}
		}
	}
}

float findZoomOffDistance(const BoundingBox *box)
{
	float farthestPoint = GeometryUtility::findDistance(box->getLowerLeftCorner(), box->getCenterPoint());
	std::cout << "farthest point distance: " << farthestPoint << std::endl;

	float perspectiveAngle = 45.0; //in degrees
	float PI = 3.14159265;
	float positionScale = farthestPoint / tan(perspectiveAngle / 2.0*PI / 180.0);

	return positionScale;
}

void calculateViewingVolume(const RenderWindow* window, float * volume)
{
	const BoundingBox *box = window->getWindowObjectsBoundingBox();
	float maxDistance = GeometryUtility::findDistance(box->getLowerLeftCorner(), box->getUpperRightCorner());
	Vec centerPoint = *(box->getCenterPoint().getCoordinates());
	Vec cameraSpaceCenterPoint = GeometryUtility::transformVector(window->getView().getLookAtMatrix(), centerPoint);

	float scrWidth = window->getView().getScreenWidth();
	float scrHeight = window->getView().getScreenHeight();

	float left, right, bottom, top;

	if (scrWidth > scrHeight) {
		float aspectRatio = scrWidth / scrHeight;
		left = cameraSpaceCenterPoint.getElementAt(1) - maxDistance * aspectRatio / 2.0;
		right = cameraSpaceCenterPoint.getElementAt(1) + maxDistance * aspectRatio / 2.0;
		bottom = cameraSpaceCenterPoint.getElementAt(2) - maxDistance / 2.0;
		top = cameraSpaceCenterPoint.getElementAt(2) + maxDistance / 2.0;
	}
	else if (scrWidth < scrHeight) {
		float aspectRatio = scrHeight / scrWidth;
		left = cameraSpaceCenterPoint.getElementAt(1) - maxDistance / 2.0;
		right = cameraSpaceCenterPoint.getElementAt(1) + maxDistance / 2.0;
		bottom = cameraSpaceCenterPoint.getElementAt(2) - maxDistance * aspectRatio / 2.0;
		top = cameraSpaceCenterPoint.getElementAt(2) + maxDistance * aspectRatio / 2.0;
	}
	else {
		left = cameraSpaceCenterPoint.getElementAt(1) - maxDistance / 2.0;
		right = cameraSpaceCenterPoint.getElementAt(1) + maxDistance / 2.0;
		bottom = cameraSpaceCenterPoint.getElementAt(2) - maxDistance / 2.0;
		top = cameraSpaceCenterPoint.getElementAt(2) + maxDistance / 2.0;
	}

	float nearby = 0.1;
	float faraway = 1.0e5;

	volume[0] = left; volume[1] = right; volume[2] = bottom; volume[3] = top;
	volume[4] = nearby; volume[5] = faraway;

	//float screenAspectRatio = (float)scrWidth / (float)scrHeight;
	//float viewingVolAspectRatio = (right - left) / (top - bottom);
	//std::cout << "Screen aspect ratio: " << screenAspectRatio << std::endl;
	//std::cout << "View Vol aspect ratio: " << viewingVolAspectRatio << std::endl;
}

void computeClickLocation(RenderWindow * window, double xPos, double yPos)
{
	double xcoord, ycoord, zcoord, wcoord;

	//screen coordinates
	xcoord = xPos;
	ycoord = yPos;
	zcoord = 0.0;
	wcoord = 0.0;

	std::cout << "Click screen coordinates: " << xcoord << " " << ycoord << std::endl;

	//normalized device coordinates
	xcoord = 2.0f* xPos / window->getView().getScreenWidth() - 1.0f;
	ycoord = 1.0f - 2.0f*yPos / window->getView().getScreenHeight();

	std::cout << "click Normalized Device coordinates: " << xcoord << " " << ycoord << std::endl;

	//homogeneous clip coordinates
	zcoord = -1.0;
	wcoord = 1.0;

	glm::vec4 vec_homo_clip(xcoord, ycoord, zcoord, wcoord);
	std::cout << "click homo clip coordinates: " << xcoord << " " << ycoord << " " << zcoord << " " << wcoord << std::endl;

	glm::vec4 homo_clip_2(xcoord, ycoord, 1.0, 1.0);

	//eye space or camera space coordinates
	glm::mat4 projectionMatrix = window->getView().getProjectionMatrixGlm();
	glm::mat4 projectionInverse = glm::inverse(projectionMatrix);

	glm::vec4 eye_vect = projectionInverse *vec_homo_clip;
	glm::vec4 eye_vect_2 = projectionInverse *homo_clip_2;

	//Now, we only needed to un - project the x, y part, so let's manually set the z,w part 
	//to mean "forwards", and "not a point". z = -1.0 shows forward direction and w set to zero 
	//means it is a direction vector and not a point. 
	//This is only true for perspective projection, it seems.

	//eye_vect[2] = 0.0;
	//eye_vect[3] = 1.0;

	xcoord = eye_vect[0]; ycoord = eye_vect[1]; zcoord = eye_vect[2]; wcoord = eye_vect[3];
	std::cout << "click eye coordinates: " << xcoord << " " << ycoord << " " << zcoord << " " << wcoord << std::endl;
	std::cout << "eye coords 2: " << eye_vect_2[0] << " " << eye_vect_2[1] << " " << eye_vect_2[2] << std::endl;

	//convert to world coordinates
	glm::mat4 viewMatrix = window->getView().getViewMatrixGlm();
	glm::mat4 viewMatInverse = glm::inverse(viewMatrix);

	glm::vec4 world_vect = viewMatInverse*eye_vect;
	glm::vec4 world_vect_2 = viewMatInverse*eye_vect_2;

	xcoord = world_vect[0]; ycoord = world_vect[1]; zcoord = world_vect[2]; wcoord = world_vect[3];

	std::cout << "click world coordinates: " << xcoord << " " << ycoord << " " << zcoord << " " << wcoord << std::endl;
	std::cout << "world coords 2: " << world_vect_2[0] << " " << world_vect_2[1] << " " << world_vect_2[2] << std::endl;

	////normalize the vector
	//glm::vec3 world_dir;d
	//world_dir[0] = world_vect[0]; world_dir[1] = world_vect[1]; world_dir[2] = world_vect[2];
	//world_dir = glm::normalize(world_dir);

	//xcoord = world_dir[0]; ycoord = world_dir[1]; zcoord = world_dir[2]; wcoord = 0.0;

	//std::cout << "click world coordinates normalized: " << xcoord << " " << ycoord << " " << zcoord << " " << wcoord << std::endl;

	Point3D segmentPoint1(world_vect[0], world_vect[1], world_vect[2]);
	Point3D segmentPoint2(world_vect_2[0], world_vect_2[1], world_vect_2[2]);

	std::vector<GeometryEntity::TriangleFace*> allTriangles = window->getRenderObjects().at(0)->getDisplayableObject()->getTriangleFaces();
	std::cout << "Total triangles: " << allTriangles.size() << std::endl;
	std::vector<GeometryEntity::TriangleFace*> intersectionTriangles;

	for (GeometryEntity::TriangleFace* face : allTriangles) {
		Vec origin = *(face->getPoints().at(0)->getCoordinates());
		Vec normal = *(face->getNormal());

		std::unique_ptr<Point3D> interSection = GeometryUtility::computePlaneSegmentIntersection(origin, normal, segmentPoint1, segmentPoint2);

		if (interSection.get() != nullptr) {
			Point3D* p = interSection.get();
			//Vec v = *(p->getCoordinates());
			/*std::cout << "plane segment intersection point: " << std::endl;
			DebugUtilities::printVector(v);*/
			bool isInsideTriangle = GeometryUtility::isPointInsideTriangle(*p, face);
			if (isInsideTriangle) {
				std::cout << "point is inside triangle: " << isInsideTriangle << std::endl;
				intersectionTriangles.push_back(face);
			}
		}
		else {
			//std::cout << "Plane segment intersection is null" << std::endl;
		}
	}

	std::cout << "total triangle intersections: " << intersectionTriangles.size() << std::endl;
}

void testTranformationPipeLine(RenderWindow * window)
{
	const std::vector<Point3D*> allPoints = window->getRenderObjects().at(0)->getDisplayableObject()->getVertices();

	Matrix viewMat = window->getView().getLookAtMatrix();
	std::cout << "View Matrix" << std::endl;
	DebugUtilities::printMatrix(viewMat);

	Matrix projectionMat = window->getView().getProjectionMatrix();
	std::cout << "Projection Matrix" << std::endl;
	DebugUtilities::printMatrix(projectionMat);

	for (int i = 0; i < allPoints.size(); i++) {
		std::cout << "---------point" << i << "----------" << std::endl;
		Point3D* pnt = allPoints.at(i);
		Matrix pointMat(4, 1);
		pointMat.setAt(1, 1, pnt->getCoordinates()->getElementAt(1));
		pointMat.setAt(2, 1, pnt->getCoordinates()->getElementAt(2));
		pointMat.setAt(3, 1, pnt->getCoordinates()->getElementAt(3));
		pointMat.setAt(4, 1, 1.0);

		Matrix eyeSpacePoint = viewMat * pointMat;
		std::cout << "eye space coordinates " << std::endl;
		DebugUtilities::printMatrix(eyeSpacePoint);

		Matrix projectionSpacePoint = projectionMat * eyeSpacePoint;
		std::cout << "projection space coordinates " << std::endl;
		DebugUtilities::printMatrix(projectionSpacePoint);

	}
}

void testTriangleSegmentIntersection(RenderWindow * window)
{
	GeometryEntity::Edge e1, e2, e3;
	Point3D p1(0.0, 0.0, 0.0);
	Point3D p2(5.0, 0.0, 0.0);
	Point3D p3(2.5, 5.0, 0.0);
	Vec normal(3);
	normal.addElement(1, 0.0).addElement(2, 0.0).addElement(3, -1.0);
	Vec origin(3);
	origin.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 0.0);

	Point3D segmentPoint1(0, 5.0, -1.0);
	Point3D segmentPoint2(0, 5.0, 1.0);

	e1.setPoints(&p1, &p2);
	e2.setPoints(&p2, &p3);
	e3.setPoints(&p3, &p1);

	GeometryEntity::TriangleFace triangleFace;
	triangleFace.setEdges(&e1, &e2, &e3);

	std::unique_ptr<Point3D> interSection = GeometryUtility::computePlaneSegmentIntersection(origin, normal, segmentPoint1, segmentPoint2);
	if (interSection.get() != nullptr) {
		Point3D* p = interSection.get();
		Vec v = *(p->getCoordinates());
		std::cout << "plane segment intersection point: " << std::endl;
		DebugUtilities::printVector(v);
		bool isInsideTriangle = GeometryUtility::isPointInsideTriangle(*(interSection.get()), &triangleFace);
		std::cout << "point is inside triangle: " << isInsideTriangle << std::endl;
	}
	else {
		std::cout << "Plane segment intersection is null" << std::endl;
	}
}

void findClickedFaceID(RenderWindow *window, unsigned int xPos, unsigned int yPos)
{
	unsigned int faceId = window->getFaceIDAtLocation(xPos, yPos);
	std::cout << "Clicked Face ID is: " << faceId << std::endl;
}




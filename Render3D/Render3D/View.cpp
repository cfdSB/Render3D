#include "View.h"

View::~View()
{
}

void View::setViewParameters(Vec position, Vec target)
{
	this->position = position;
	this->target = target;

	positionMat.copyColumn(4, position.scale(-1.0));
	computeLookAtMatrix();
}

void View::setProjectionParameters(float projectionAngle, unsigned int scrWidth, unsigned int scrHeight)
{
	this->projectionAngle = projectionAngle;
	this->scrWidth = scrWidth;
	this->scrHeight = scrHeight;

	computeProjectionMatrix();
}

void View::computeLookAtMatrix()
{
	Vec tmp = position - target;
	//std::cout << "tmp vector" << std::endl;
	//DebugUtilities::printVector(tmp);

	cameraDirection = tmp.normalize();
	//std::cout << "camera direction" << std::endl;
	//DebugUtilities::printVector(cameraDirection);

	tmpUp = Vec(3);
	tmpUp.addElement(1, 0.0).addElement(2, 0.0).addElement(3, 1.0);

	Vec tmp2 = tmpUp ^ cameraDirection;
	cameraRight = tmp2.normalize();
	//std::cout << "camera Right" << std::endl;
	//DebugUtilities::printVector(cameraRight);

	Vec tmp3 = cameraDirection ^ cameraRight;
	cameraUp = tmp3.normalize();
	//std::cout << "camera up" << std::endl;
	//DebugUtilities::printVector(cameraUp);

	Matrix cameraCS(4, 4);
	cameraCS.copyRow(1, cameraRight);
	cameraCS.copyRow(2, cameraUp);
	cameraCS.copyRow(3, cameraDirection);
	//std::cout << "Camera CS matrix" << std::endl;
	//DebugUtilities::printMatrix(cameraCS);

	lookAt = cameraCS * positionMat;
}

void View::computeProjectionMatrix()
{
	glm::mat4 projectionMat = glm::perspective(glm::radians(projectionAngle), (float)scrWidth / (float)scrHeight, 0.1f, 1.0e5f);
	projection = convertGlmMatrix(projectionMat);
}

Matrix View::convertGlmMatrix(glm::mat4& m) {
	Matrix convert(4, 4);

	for (int i = 1; i <= 4; i++) {
		glm::vec4 vect = glm::vec4(m[i - 1]);
		Vec v(4);
		for (int j = 1; j <= 4; j++) {
			v.addElement(j, vect[j - 1]);
		}
		convert.copyColumn(i, v);
	}

	return convert;
}
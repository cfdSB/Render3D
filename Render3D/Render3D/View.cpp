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

const Matrix& View::getLookAtMatrix() const
{
	return lookAt;
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

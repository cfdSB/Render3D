#ifndef VIEW_H
#define VIEW_H

#include "Vec.h"
#include "Matrix.h"
#include "DebugUtilities.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class View
{
private:
	Vec position, target, tmpUp;
	Vec cameraDirection, cameraRight, cameraUp;
	Matrix lookAt = Matrix(4, 4);
	Matrix positionMat = Matrix(4, 4);
	Matrix projection = Matrix(4, 4);
	float projectionAngle = 45.0;
	unsigned int scrWidth=800, scrHeight=600;
public:
	View() { };
	virtual ~View();
	const Vec& getCameraDirection() const { return cameraDirection; };
	const Vec& getCameraRight() const { return cameraRight; };
	const Vec& getCameraUp() const { return cameraUp; };
	const Vec& getCameraPosition() const { return position; };
	const Vec& getCameraTarget() const { return target; }
	void setViewParameters(Vec position, Vec target);
	const Matrix& getLookAtMatrix() const { return lookAt; };
	const Matrix& getProjectionMatrix() const { return projection; };
	void setProjectionParameters(float projectionAngle, unsigned int scrWidth, unsigned int scrHeight);

private:
	void computeLookAtMatrix();
	void computeProjectionMatrix();
	Matrix convertGlmMatrix(glm::mat4& m);
};
#endif


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
public:
	enum PROJECTION_TYPE { Parallel, Perpective};
private:
	Vec position, target, tmpUp;
	Vec cameraDirection, cameraRight, cameraUp;
	glm::mat4 projectionGlm;
	Matrix lookAt = Matrix(4, 4);
	Matrix positionMat = Matrix(4, 4);
	Matrix projection = Matrix(4, 4);
	float projectionAngle = 45.0;
	unsigned int scrWidth=800, scrHeight=600;
	PROJECTION_TYPE projectionType = PROJECTION_TYPE::Parallel;
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
	unsigned int getScreenWidth() const { return scrWidth; };
	unsigned int getScreenHeight() const { return scrHeight; };
	glm::mat4 getProjectionMatrixGlm() const { return projectionGlm; };
	glm::mat4 getViewMatrixGlm() const;
	void setProjectionType(PROJECTION_TYPE type);
	PROJECTION_TYPE getProjectionType() const { return projectionType; };

private:
	void computeLookAtMatrix();
	void computeProjectionMatrix();
	Matrix convertGlmMatrix(glm::mat4& m);
	void computeOrthoGraphicProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
};
#endif


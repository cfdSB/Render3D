#ifndef VIEW_H
#define VIEW_H

#include "Vec.h"
#include "Matrix.h"
#include "DebugUtilities.h"

class View
{
private:
	Vec position, target, tmpUp;
	Vec cameraDirection, cameraRight, cameraUp;
	Matrix lookAt = Matrix(4, 4);
	Matrix positionMat = Matrix(4, 4);
public:
	View() { };
	virtual ~View();
	const Vec& getCameraDirection() { return cameraDirection; };
	const Vec& getCameraRight(){ return cameraRight; };
	const Vec& getCameraUp() { return cameraUp; };
	void setViewParameters(Vec position, Vec target);
	const Matrix& getLookAtMatrix();

private:
	void computeLookAtMatrix();


};
#endif


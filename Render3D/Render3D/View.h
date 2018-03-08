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
	const Vec& getCameraDirection() const { return cameraDirection; };
	const Vec& getCameraRight() const { return cameraRight; };
	const Vec& getCameraUp() const { return cameraUp; };
	const Vec& getCameraPosition() const { return position; };
	const Vec& getCameraTarget() const { return target; }
	void setViewParameters(Vec position, Vec target);
	const Matrix& getLookAtMatrix() const;

private:
	void computeLookAtMatrix();


};
#endif


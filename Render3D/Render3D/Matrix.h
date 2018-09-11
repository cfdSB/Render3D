#ifndef MATRIX_H
#define MATRIX_H


//namespace Render3D {
#include "Vec.h"
	class Matrix
	{
	private:
		int nRows, nColumns;
		float *data;

		void initializeToIdentity();
		void zeroIndexedSetAt(int row, int column, float value);

	public:
		Matrix(int rows, int columns);
		virtual ~Matrix();
		float getAt(int row, int column) const;
		void setAt(int row, int column, float value);
		Matrix operator* (const Matrix& m) const;
		Matrix(const Matrix& m);
		Matrix& operator=(const Matrix& m);
		void copyRow(int rowNumber, const Vec& v);
		void copyColumn(int columnNumber, const Vec& v);
		int getNumberOfRows() const { return nRows; };
		int getNumberOfColumns() const { return nColumns; };
		const float* getDataPtr() const { return data; };
		Vec getColumn(int columnNumber);

	};
//}
#endif

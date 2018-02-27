#include "Matrix.h"
#include <iostream>

void Matrix::initializeToIdentity() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nColumns; j++) {
			if (i == j) {
				zeroIndexedSetAt(i, j, 1);
			}
			else {
				zeroIndexedSetAt(i, j, 0);
			}
		}
	}
}

void Matrix::zeroIndexedSetAt(int row, int column, float value) {
	data[row*nColumns + column] = value;
}

Matrix::Matrix(int rows, int columns) :nRows(rows), nColumns(columns) {
		data = new float[nRows*nColumns];
		initializeToIdentity();

	}

Matrix::~Matrix() {
		if (data)
			delete[] data;
	}

float Matrix::getAt(int row, int column) const {
		int location = (row - 1)*nColumns + column - 1;
		return data[location];
	}

void Matrix::setAt(int row, int column, float value) {
		zeroIndexedSetAt(row - 1, column - 1, value);
	}

Matrix Matrix:: operator*(const Matrix& m) {
	int rows = this->nRows;
	int columns = m.nColumns;

	Matrix mNew(rows, columns);
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			double val=0;
			for (int m1C = 1; m1C <= m.nRows; m1C++) {
				val = val + this->getAt(i, m1C)*m.getAt(m1C, j);
			}
			//std::cout << val << std::endl;
			mNew.setAt(i, j, val);
		}
	}
	return mNew;
}

Matrix::Matrix(const Matrix &m)
{
	nRows = m.nRows;
	nColumns = m.nColumns;
	if (m.data) {
		data = new float[nRows*nColumns];
		for (int i = 0; i < nRows; i++) {
			for (int j = 0; j < nColumns; j++) {
				zeroIndexedSetAt(i, j, m.getAt(i + 1, j + 1));
			}
		}
	}
	else {
		data = nullptr;
	}
}

Matrix& Matrix::operator=(const Matrix &m)
{
	if (this == &m) {
		return *this;
	}
	if (data)
		delete[] data;

	nRows = m.nRows;
	nColumns = m.nColumns;
	if (m.data) {
		data = new float[nRows*nColumns];

		for (int i = 0; i < nRows; i++) {
			for (int j = 0; j < nColumns; j++) {
				zeroIndexedSetAt(i, j, m.getAt(i + 1, j + 1));
			}
		}
	}
	else
		data = nullptr;

	return *this;
}

void Matrix::copyRow(int rowNumber, const Vec & v)
{
	for (int i = 1; i <= v.getSize(); i++) {
		this->zeroIndexedSetAt(rowNumber - 1, i - 1, v.getElementAt(i));
	}
}

void Matrix::copyColumn(int columnNumber, const Vec & v)
{
	for (int i = 1; i <= v.getSize(); i++) {
		this->zeroIndexedSetAt(i - 1, columnNumber-1, v.getElementAt(i));
	}
}

Vec Matrix::getColumn(int columnNumber)
{
	Vec column(nRows);
	for (int i = 1; i <= nRows; i++) {
		column.addElement(i, this->getAt(i, columnNumber));
	}
	return column;
}

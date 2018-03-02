#include "DebugUtilities.h"



DebugUtilities::DebugUtilities()
{
}


DebugUtilities::~DebugUtilities()
{
}

void DebugUtilities::printVector(Vec & v)
{
	for (int i = 1; i <= v.getSize(); i++) {
		std::cout << v.getElementAt(i) << " ";
	}
	std::cout << std::endl;
}

void DebugUtilities::printMatrix(Matrix & m)
{
	for (int i = 1; i <= m.getNumberOfRows(); i++) {
		for (int j = 1; j <= m.getNumberOfColumns(); j++) {
			std::cout << m.getAt(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

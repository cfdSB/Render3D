#ifndef VEC_H
#define VEC_H
class Vec
{
private:
	int size;
	float *data;

private:
	void initializeVector();

public:
	Vec(int size);
	virtual ~Vec();
	Vec(const Vec& v);
	Vec& operator=(const Vec& v);
	Vec operator^(const Vec& v);	//cross product
	Vec operator+(const Vec& v);	//addition
	Vec operator-(const Vec& v);	//subtraction
	Vec operator*(const Vec& v);	//dot product
	Vec& addElement(int index, float element);
	float getElementAt(int index) const { return data[index - 1]; };
	Vec normalize();
	int getSize() const { return size; };
	Vec scale(float val);
	void initializeElements(float value);
	void copy(const Vec& v);
};
#endif



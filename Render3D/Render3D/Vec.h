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
	Vec();
	Vec(int size);
	virtual ~Vec();
	Vec(const Vec& v);
	Vec& operator=(const Vec& v);
	Vec operator^(const Vec& v) const;	//cross product
	Vec operator+(const Vec& v) const;	//addition
	Vec operator-(const Vec& v) const;	//subtraction
	float operator*(const Vec& v) const;	//dot product
	Vec& addElement(int index, float element);
	float getElementAt(int index) const { return data[index - 1]; };
	Vec normalize();
	int getSize() const { return size; };
	Vec scale(float val) const;
	void initializeElements(float value);
	void copy(const Vec& v);
	const float* getDataPtr() const { return data; };
};
#endif



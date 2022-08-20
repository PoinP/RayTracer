#ifndef VECTOR3_HEADER

#define VECTOR3_HEADER

#include <iostream>

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3& other);

	Vector3& operator=(const Vector3& other);

	Vector3 operator-() const;

	double operator[](int index) const;
	double& operator[](int index);

	Vector3& operator+=(const Vector3& otherVec);
	Vector3& operator*=(double scalar);
	Vector3& operator/=(double scalar);

	double x() const;
	double y() const;
	double z() const;

	double length() const;
	double lengthSquared() const;

private:
	double m_Coords[3];
};

using Point3 = Vector3;
using Color = Vector3;

void operator<<(std::ostream& stream, const Vector3& vector);

Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
Vector3 operator*(const Vector3& vector, double scalar);
Vector3 operator*(double scalar, const Vector3& vector);
Vector3 operator/(const Vector3& vector, double scalar);
Vector3 operator/(double scalar, const Vector3& vector);

double dotProduct(const Vector3& vector1, const Vector3& vector2);
Vector3 crossProduct(const Vector3& vector1, const Vector3& vector2);
Vector3 unitVector(const Vector3& vector);

#endif // !VECTOR3_HEADER
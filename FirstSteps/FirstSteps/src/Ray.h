#ifndef RAY_H

#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray();
	Ray(const Vector3& origin, const Vector3& direction);

	const Vector3& origin() const;
	const Vector3& direction() const;

	Vector3 at(double scalar) const;
private:
	Vector3 m_Origin;
	Vector3 m_Direction;
};

#endif // !RAY_H

#ifndef RAY_H

#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray();
	Ray(const Vector3& origin, const Vector3& direction, double time);

	const Vector3& origin() const;
	const Vector3& direction() const;
	const double& time() const;

	Vector3 at(double scalar) const;
private:
	Vector3 m_Origin;
	Vector3 m_Direction;

	double m_Time{};
};

#endif // !RAY_H

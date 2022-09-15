#ifndef AABB_H

#define AABB_H

#include "Vector3.h"
#include "Ray.h"

// Axis-Aligned Bounding Boxes

class AABB
{
public:
	AABB();
	AABB(const Point3& min, const Point3& max);

	const Point3& min() const;
	const Point3& max() const;

	bool isHit(const Ray& ray, double tMin, double tMax) const;

	static AABB surroundingBox(const AABB& box0, const AABB& box1);

private:
	 Point3 m_Min;
	 Point3 m_Max;

};

#endif // !AABB_H
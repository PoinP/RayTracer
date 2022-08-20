#ifndef HITTABLE_H

#define HITTABLE_H

#include "Vector3.h"
#include "Ray.h"

struct HitRecord 
{
	Point3 hitPoint;
	Vector3 normalVector;
	double t;
	bool frontFacing{};

	void setFaceNormal(const Ray& ray, const Vector3& outwardNormal)
	{
		frontFacing = dotProduct(ray.direction(), outwardNormal) < 0;
		normalVector = frontFacing ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const = 0;
};

#endif // !HITTABLE_H
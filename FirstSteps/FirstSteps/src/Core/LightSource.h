#ifndef LIGHT_SOURCE_H

#define LIGHT_SOURCE_H

#include "Vector3.h"
#include "../Hittables/HittableList.h"

class LightSource
{
public:
	LightSource(const Point3& origin, double softness);

	bool isInShadow(const Ray& ray, const HitRecord& record, const HittableList& world) const;

private:
	Point3 m_Origin;
	double m_Softness;
};

#endif // !LIGHT_SOURCE_H
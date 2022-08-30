#ifndef MOVING_SPHERE_H

#define MOVING_SPHERE_H

#include "Vector3.h"
#include "Hittable.h"

class MovingSphere : public Hittable
{
public:
	MovingSphere(const Point3& center0, const Point3& center1, double radius, double time0, double time1, Material* materialPtr);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;

	Point3 center(double time) const;

private:
	Point3 m_Center0;
	Point3 m_Center1;
	double m_Radius;
	double m_Time0;
	double m_Time1;
	Material* m_MaterialPtr;
};

#endif // !MOVING_SPHERE_H
#ifndef SPHERE_H

#define SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
	Sphere(const Point3& center, double radius, Material* material);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
private:
	Point3 m_Center;
	double m_Radius;
	Material* m_MaterialPtr;
};

#endif // !SPHERE_H
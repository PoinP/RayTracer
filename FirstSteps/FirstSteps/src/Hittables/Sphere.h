#ifndef SPHERE_H

#define SPHERE_H

#include "../Core/Vector3.h"
#include "../Core/Ray.h"
#include "../Hittables/Hittable.h"
#include "../Materials/Material.h"

class Sphere : public Hittable
{
public:
	Sphere(const Point3& center, double radius, Material* material);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;

private:
	Point3 m_Center;
	double m_Radius;
	Material* m_MaterialPtr;

	static void getSphereUV(const Point3& p, double& u, double& v);
};

#endif // !SPHERE_H
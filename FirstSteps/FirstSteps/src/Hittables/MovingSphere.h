#ifndef MOVING_SPHERE_H

#define MOVING_SPHERE_H

#include "../Core/Vector3.h"
#include "../Hittables/Hittable.h"

#include <memory>

class MovingSphere : public Hittable
{
public:
	MovingSphere(const Point3& center0, const Point3& center1, double radius, double time0, double time1, const Material* materialPtr);
	MovingSphere(const Point3& center0, const Point3& center1, double radius, double time0, double time1, const std::shared_ptr<const Material>& materialPtr);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;

private:
	Point3 m_Center0;
	Point3 m_Center1;
	double m_Radius;
	double m_Time0;
	double m_Time1;
	std::shared_ptr<const Material> m_MaterialPtr;

	Point3 center(double time) const;
};

#endif // !MOVING_SPHERE_H
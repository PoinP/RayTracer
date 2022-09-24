#ifndef BOX_H

#define BOX_H

#include "Hittable.h"
#include "Plane.h"
#include "HittableList.h"
#include "../Materials/Material.h"

#include <memory>

class Box : public Hittable
{
public:
	Box(const Point3& origin, const Point3& dimensions, std::shared_ptr<Material>);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	HittableList m_Planes;
	Point3 m_Origin, m_Dimension;
	std::shared_ptr<Material> m_MaterialPtr;
};

#endif // !BOX_H
#ifndef TRANSLATE_H

#define TRANSLATE_H

#include "Hittable.h"
#include "../Core/Vector3.h"

#include <memory>

class Translate : public Hittable
{
public:
	Translate(const std::shared_ptr<Hittable>& object, const Vector3& offset);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	std::shared_ptr<Hittable> m_Object;
	Vector3 m_Offset;
};

void translate(std::shared_ptr<Hittable>& obj, const Vector3& offset);

#endif // !TRANSLATE_H
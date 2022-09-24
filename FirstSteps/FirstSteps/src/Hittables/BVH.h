#ifndef BVH_H

#define BVH_H

#include "Hittable.h"
#include "HittableList.h"

#include <memory>

class BVH : public Hittable
{
public:
	BVH();
	BVH(const HittableList& objectsSource, double time0, double time1);
	BVH(const HittableList& objectsSource, unsigned start, unsigned end, double time0, double time1);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	std::shared_ptr<Hittable> m_Left;
	std::shared_ptr<Hittable> m_Right;
	AABB m_Box;

	static bool boxCompare(const std::shared_ptr<Hittable> obj0, const std::shared_ptr<Hittable> obj1, int axis);

	static bool boxCompareX(const std::shared_ptr<Hittable> obj0, const std::shared_ptr<Hittable> obj1);
	static bool boxCompareY(const std::shared_ptr<Hittable> obj0, const std::shared_ptr<Hittable> obj1);
	static bool boxCompareZ(const std::shared_ptr<Hittable> obj0, const std::shared_ptr<Hittable> obj1);

};

#endif // !BVH_H
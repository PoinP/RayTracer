#ifndef BVH_H

#define BVH_H

#include "Hittable.h"
#include "HittableList.h"


class BVH : public Hittable
{
public:
	BVH();
	BVH(const HittableList& objectsSource, double time0, double time1);
	BVH(const HittableList& objectsSource, unsigned start, unsigned end, double time0, double time1);
	~BVH();

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;

private:
	Hittable* m_Left;
	Hittable* m_Right;
	AABB m_Box;

	static bool boxCompare(const Hittable* obj0, const Hittable* obj1, int axis);

	static bool boxCompareX(const Hittable* obj0, const Hittable* obj1);
	static bool boxCompareY(const Hittable* obj0, const Hittable* obj1);
	static bool boxCompareZ(const Hittable* obj0, const Hittable* obj1);

};

#endif // !BVH_H
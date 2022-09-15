#include "BVH.h"

#include "../Utility/Utility.h"

#include <algorithm>

BVH::BVH()
	: m_Left(nullptr), m_Right(nullptr)
{
}

BVH::BVH(const HittableList& objectsSource, double time0, double time1)
	: BVH(objectsSource, 0, objectsSource.getSize(), time0, time1)
{
}

BVH::BVH(const HittableList& objectsSource, unsigned start, unsigned end, double time0, double time1)
{
	HittableList objects = objectsSource;
	int axis = randomInt(0, 2);

	unsigned objectSpan = end - start;

	auto comparator = 
		axis == 0 ? BVH::boxCompareX :
		axis == 1 ? BVH::boxCompareY :
					BVH::boxCompareZ;

	if (objectSpan == 1)
	{
		m_Left = m_Right = objects.getData()[start];
	}
	else if (objectSpan == 2)
	{
		if (comparator(objects.getData()[start], objects.getData()[start + 1]))
		{
			m_Left = objects.getData()[start];
			m_Right = objects.getData()[start + 1];
		}
		else
		{
			m_Left = objects.getData()[start + 1];
			m_Right = objects.getData()[start];
		}
	}
	else
	{	
		std::sort(objects.begin(), (objects.begin() + end), comparator);

		unsigned mid = start + objectSpan / 2;

		m_Left = new BVH(objects, start, mid, time0, time1);
		m_Right = new BVH(objects, mid, end, time0, time1);
	}

	AABB boxLeft, boxRight;

	m_Left->hasBoundingBox(0, 0, boxLeft);
	m_Right->hasBoundingBox(0, 0, boxRight);

	m_Box = AABB::surroundingBox(boxLeft, boxRight);
}

BVH::~BVH()
{
	delete m_Left;
	delete m_Right;
}

bool BVH::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
	if (!m_Box.isHit(ray, minT, maxT))
		return false;

	bool leftHit = m_Left->isHit(ray, minT, maxT, record);
	bool rightHit = m_Right->isHit(ray, minT, leftHit ? record.t : maxT, record);

	return leftHit || rightHit;
}

bool BVH::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
	boundingBox = m_Box;
	return true;
}

bool BVH::boxCompare(const Hittable* obj0, const Hittable* obj1, int axis)
{
	AABB box0, box1;

	obj0->hasBoundingBox(0.0, 0.0, box0);
	obj1->hasBoundingBox(0.0, 0.0, box1);

	return box0.min()[axis] < box1.min()[axis];
}

bool BVH::boxCompareX(const Hittable* obj0, const Hittable* obj1) { return boxCompare(obj0, obj1, 0); }
bool BVH::boxCompareY(const Hittable* obj0, const Hittable* obj1) { return boxCompare(obj0, obj1, 1); }
bool BVH::boxCompareZ(const Hittable* obj0, const Hittable* obj1) { return boxCompare(obj0, obj1, 2); }

#ifndef HITTABLE_LIST_H

#define HITTABLE_LIST_H

#include "Hittable.h"

class HittableList
{
public:
	HittableList();
	HittableList(Hittable* obj);
	HittableList(const HittableList& other);
	~HittableList();

	HittableList& operator=(const HittableList& other);

	bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const;

	void add(Hittable* obj);
	void clear();
private:
	int m_Size;
	int m_Capacity;
	Hittable** m_Objects;

	void resize(unsigned int newSize);
	unsigned int calculateNewCapacity();
};

#endif // !HITTABLE_LIST_H
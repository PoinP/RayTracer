#ifndef HITTABLE_LIST_H

#define HITTABLE_LIST_H

#include "../Hittables/Hittable.h"
#include "../Core/AABB.h"

class HittableIterator
{
public:

	using difference_type = std::ptrdiff_t;
	using value_type = Hittable*;
	using pointer = Hittable**;
	using reference = Hittable*&;
	using iterator_category = std::random_access_iterator_tag;

	HittableIterator(Hittable** ptr);

	HittableIterator& operator++();
	HittableIterator operator++(int);
	HittableIterator& operator--();
	HittableIterator operator--(int);
	HittableIterator& operator+=(difference_type offset);
	HittableIterator& operator-=(difference_type offset);

	bool operator==(const HittableIterator& other) const;
	bool operator!=(const HittableIterator& other) const;

	bool operator<(const HittableIterator& other) const;
	bool operator>(const HittableIterator& other) const;
	bool operator<=(const HittableIterator& other) const;
	bool operator>=(const HittableIterator& other) const;

	pointer operator->();
	reference operator*();
	reference operator*() const;
	reference operator[](difference_type index);

	pointer getPtr() const noexcept;

private:
	pointer m_Ptr;
};

inline HittableIterator operator+(int offset, const HittableIterator& it)
{
	return HittableIterator(it.getPtr() + offset);
}

inline HittableIterator operator+(const HittableIterator& it, int offset)
{
	return offset + it.getPtr();
}

inline HittableIterator operator-(const HittableIterator& it, int offset)
{
	return it.getPtr() - offset;
}

inline std::ptrdiff_t operator-(const HittableIterator& lhs, const HittableIterator& rhs)
{
	return lhs.getPtr() - rhs.getPtr();
}

class HittableList : public Hittable
{
public:
	HittableList();
	HittableList(Hittable* obj);
	HittableList(const HittableList& other);
	~HittableList();

	HittableList& operator=(const HittableList& other);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;

	HittableIterator begin() const noexcept;
	HittableIterator end() const noexcept;

	Hittable** getData() noexcept;
	Hittable* const * getData() const noexcept;

	int getSize() const noexcept;

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
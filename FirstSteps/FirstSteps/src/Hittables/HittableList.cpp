#include "HittableList.h"

HittableIterator::HittableIterator(pointer ptr)
    : m_Ptr(ptr)
{
}

HittableIterator& HittableIterator::operator++()
{
    ++m_Ptr;
    return *this;
}

HittableIterator HittableIterator::operator++(int)
{
    HittableIterator old = *this;
    ++(*this);
    return old;
}

HittableIterator& HittableIterator::operator--()
{
    --m_Ptr;
    return *this;
}

HittableIterator HittableIterator::operator--(int)
{
    HittableIterator old = *this;
    --(*this);
    return old;
}

HittableIterator& HittableIterator::operator+=(difference_type offset)
{
    m_Ptr += offset;
    return *this;
}

HittableIterator& HittableIterator::operator-=(difference_type offset)
{
    m_Ptr -= offset;
    return *this;
}

bool HittableIterator::operator==(const HittableIterator& other) const
{
    return m_Ptr == other.m_Ptr;
}

bool HittableIterator::operator!=(const HittableIterator& other) const
{
    return !(*this == other);
}

bool HittableIterator::operator<(const HittableIterator& other) const
{
    return other - *this > 0;
}

bool HittableIterator::operator>(const HittableIterator& other) const
{
    return other < *this;
}

bool HittableIterator::operator<=(const HittableIterator& other) const
{
    return !(*this > other);
}

bool HittableIterator::operator>=(const HittableIterator& other) const
{
    return !(*this < other);
}

std::shared_ptr<Hittable>* HittableIterator::operator->()
{
    return m_Ptr;
}

std::shared_ptr<Hittable>& HittableIterator::operator*()
{
    return *m_Ptr;
}

std::shared_ptr<Hittable>& HittableIterator::operator*() const
{
    return *m_Ptr;
}

std::shared_ptr<Hittable>& HittableIterator::operator[](difference_type index)
{
    return *(m_Ptr + index);
}

std::shared_ptr<Hittable>* HittableIterator::getPtr() const noexcept
{
    return m_Ptr;
}

HittableList::HittableList()
    : m_Size(0), m_Capacity(0), m_Objects(nullptr)
{}

HittableList::HittableList(std::shared_ptr<Hittable> obj)
    : m_Size(1), m_Capacity(1), m_Objects(new std::shared_ptr<Hittable>[m_Capacity])
{
    m_Objects[0] = obj;
}

HittableList::HittableList(const HittableList& other)
    : m_Size(other.m_Size), m_Capacity(other.m_Capacity), m_Objects(new std::shared_ptr<Hittable>[m_Capacity])
{
    for (int i = 0; i < other.m_Size && i < m_Capacity; i++)
    {
        m_Objects[i] = other.m_Objects[i];
    }
}

HittableList::~HittableList()
{
    delete[] m_Objects;
}

HittableList& HittableList::operator=(const HittableList& other)
{
    if (this != &other)
    {
        delete[] m_Objects;

        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Objects = new std::shared_ptr<Hittable>[m_Capacity];

        for (int i = 0; i < m_Size && i < m_Capacity; i++)
        {
            m_Objects[i] = other.m_Objects[i];
        }
    }

    return *this;
}

bool HittableList::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    HitRecord tempRecord;
    double closestObject = maxT;
    bool hasHit = false;

    for (int i = 0; i < m_Size; i++)
    {
        if (m_Objects[i]->isHit(ray, minT, closestObject, tempRecord))
        {
            hasHit = true;
            closestObject = tempRecord.t;
            record = tempRecord;
        }
    }

    return hasHit;
}

bool HittableList::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
    if (m_Size == 0) 
        return false;

    AABB tempBox;
    bool firstBox = true;

    for (auto object : (*this))
    {
        if (!object->hasBoundingBox(time0, time1, tempBox))
            return false;

        boundingBox = firstBox ? tempBox : AABB::surroundingBox(boundingBox, tempBox);
        firstBox = false;
    }

    return true;
}

Point3 HittableList::getCenter() const
{
    return Point3(0, 0, 0);
}

Point3 HittableList::getOrigin() const
{
    return Point3(0, 0, 0);
}

HittableIterator HittableList::begin() const noexcept
{
    return HittableIterator(m_Objects);
}

HittableIterator HittableList::end() const noexcept
{
    return HittableIterator(m_Objects + m_Size);
}

std::shared_ptr<Hittable>* HittableList::getData() noexcept
{
    return m_Objects;
}

std::shared_ptr<Hittable> const * HittableList::getData() const noexcept
{
    return m_Objects;
}

int HittableList::getSize() const noexcept
{
    return m_Size;
}

void HittableList::add(std::shared_ptr<Hittable> obj)
{
    if (m_Size >= m_Capacity)
        resize(calculateNewCapacity());

    m_Objects[m_Size++] = obj;
}

void HittableList::clear()
{
    delete[] m_Objects;
    m_Size = 0;
    m_Capacity = 0;
    m_Objects = nullptr;
}

void HittableList::resize(unsigned int newSize)
{
    std::shared_ptr<Hittable>* newList = new std::shared_ptr<Hittable>[newSize];

    for (int i = 0; i < m_Size && i < (int)newSize; i++)
    {
        newList[i] = m_Objects[i];
    }

    delete[] m_Objects;
    m_Capacity = newSize;
    m_Objects = newList;
}

unsigned int HittableList::calculateNewCapacity()
{
    if (m_Capacity < 1) return 1;
    if (m_Capacity < 2) return 2;
    if (m_Capacity < 4) return 4;
    if (m_Capacity < 8) return 8;
    if (m_Capacity < 16) return 16;

    return ((m_Capacity / 16) + 1) * 16;
}

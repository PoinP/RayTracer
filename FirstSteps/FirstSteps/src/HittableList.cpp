#include "HittableList.h"

HittableList::HittableList()
    : m_Size(0), m_Capacity(0), m_Objects(nullptr)
{}

HittableList::HittableList(Hittable* obj)
    : m_Size(1), m_Capacity(1), m_Objects(new Hittable*[m_Capacity])
{
    m_Objects[0] = obj;
}

HittableList::HittableList(const HittableList& other)
    : m_Size(other.m_Size), m_Capacity(other.m_Capacity), m_Objects(new Hittable*[m_Capacity])
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
        m_Objects = new Hittable*[m_Capacity];

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

void HittableList::add(Hittable* obj)
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
    Hittable** newList = new Hittable*[newSize];

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

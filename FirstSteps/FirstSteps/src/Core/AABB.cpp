#include "AABB.h"

AABB::AABB()
{
}

AABB::AABB(const Point3& min, const Point3& max)
    : m_Min(min), m_Max(max)
{
}

const Point3& AABB::min() const
{
    return m_Min;
}

const Point3& AABB::max() const
{
    return m_Max;
}

bool AABB::isHit(const Ray& ray, double tMin, double tMax) const
{
    double t0, t1;

    for (int i = 0; i < 3; i++)
    {
        t0 = (m_Min[i] - ray.origin()[i]) / ray.direction()[i];
        t1 = (m_Max[i] - ray.origin()[i]) / ray.direction()[i];

        double temp = t0;
        t0 = fmin(t0, t1);
        t1 = fmax(temp, t1);

        tMin = fmax(t0, tMin);
        tMax = fmin(t1, tMax);

        if (tMin >= tMax)
            return false;
    }

    return true;
}

AABB AABB::surroundingBox(const AABB& box0, const AABB& box1)
{
    Point3 min = Point3(
        fmin(box0.m_Min.x(), box1.m_Min.x()),
        fmin(box0.m_Min.y(), box1.m_Min.y()),
        fmin(box0.m_Min.z(), box1.m_Min.z())
    );

    Point3 max = Point3(
        fmax(box0.m_Max.x(), box1.m_Max.x()),
        fmax(box0.m_Max.y(), box1.m_Max.y()),
        fmax(box0.m_Max.z(), box1.m_Max.z())
    );

    return AABB(min, max);
}

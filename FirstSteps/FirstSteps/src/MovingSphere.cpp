#include "MovingSphere.h"

MovingSphere::MovingSphere(const Point3& center0, const Point3& center1, double radius, double time0, double time1, Material* materialPtr)
    : m_Center0(center0), m_Center1(center1), m_Radius(radius), m_Time0(time0), m_Time1(time1), m_MaterialPtr(materialPtr)
{
}

bool MovingSphere::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    Point3 diff = ray.origin() - center(ray.time());

    double a = ray.direction().lengthSquared();
    double halfB = dotProduct(ray.direction(), diff);
    double c = diff.lengthSquared() - m_Radius * m_Radius;
    double discriminant = halfB * halfB - a * c;

    if (discriminant < 0)
        return false;

    double sqrtDiscriminant = sqrt(discriminant);

    double root = (-halfB - sqrtDiscriminant) / a;

    if (root < minT || root > maxT)
    {
        root = (-halfB + sqrtDiscriminant) / a;
        if (root < minT || root > maxT)
            return false;
    }

    record.t = root;
    record.hitPoint = ray.at(record.t);
    record.materialPtr = m_MaterialPtr;
    record.normalVector = (record.hitPoint - center(ray.time())) / m_Radius;
    record.setFaceNormal(ray, record.normalVector);

    return true;
}

Point3 MovingSphere::center(double time) const
{
    return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
}

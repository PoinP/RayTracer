#include "Sphere.h"

Sphere::Sphere(const Point3& center, double radius, Material* material)
    : m_Center(center), m_Radius(radius), m_MaterialPtr(material)
{
}

bool Sphere::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    Vector3 diff = ray.origin() - m_Center;
    double a = ray.direction().lengthSquared();
    double halfB = dotProduct(ray.direction(), diff);
    double c = diff.lengthSquared() - m_Radius * m_Radius;
    double discriminant = halfB * halfB - a * c;

    if (discriminant < 0)
        return false;

    double sqrtDisc = sqrt(discriminant);

    double root = (-halfB - sqrtDisc) / a;

    if (root < minT || root > maxT)
    {
        root = (-halfB + sqrtDisc) / a;
        if (root < minT || root > maxT)
            return false;
    }

    record.t = root;
    record.hitPoint = ray.at(record.t);
    Vector3 normalVector = (record.hitPoint - m_Center) / m_Radius; // (why dividing by radius?) We divide by radius because we need a normal unit vector!
    record.setFaceNormal(ray, normalVector);
    record.materialPtr = m_MaterialPtr;
    
    return true;
}

bool Sphere::hasBoundingBox(double t0, double t1, AABB& boundingBox) const
{
    boundingBox = AABB(
        m_Center - Vector3(m_Radius, m_Radius, m_Radius),
        m_Center + Vector3(m_Radius, m_Radius, m_Radius)
    );

    return true;
}

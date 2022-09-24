#include "Sphere.h"
#include "../Utility/Utility.h"

#include <cmath>

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> material)
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
    getSphereUV(normalVector, record.u, record.v);
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

Point3 Sphere::getCenter() const
{
    return m_Center;
}

Point3 Sphere::getOrigin() const
{
    return getCenter();
}

void Sphere::getSphereUV(const Point3& p, double& u, double& v)
{
    double radius = p.length();
    double phi = atan2(p.z(), -p.x());
    double theta = acos(p.y() / radius);

    u = (phi / (2 * PI) + 0.5);
    v = theta / PI;

    //u = 1 - (phi / (2 * PI) + 0.5);
    //v = 1 - theta / PI;

    ////double theta = acos(p.y() / 0.5);
    ////double phi = atan2(p.x(), p.z());

    //////////u = 0.5 + atan2(p.z(), p.x()) / (2 * PI);
    //////////v = 0.5 - asin(p.y()) / PI;


    //////////////double theta = acos(-p.y());
    //////////////double phi = atan2(-p.z(), p.x()) + PI;

    //////////////u = phi / (2 * PI);
    //////////////v = theta / PI;
}

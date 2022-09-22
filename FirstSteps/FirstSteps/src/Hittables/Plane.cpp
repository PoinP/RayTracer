#include "Plane.h"
#include "../Core/AABB.h"

XYPlane::XYPlane(double x0, double x1, double y0, double y1, double k, const Material* material)
    : m_X0(x0), m_X1(x1), m_Y0(y0), m_Y1(y1), m_K(k), m_MaterialPtr(material)
{
}

bool XYPlane::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    double t = (m_K - ray.origin().z()) / ray.direction().z();

    if (minT > t || maxT < t)
        return false;

    double x = ray.origin().x() + t * ray.direction().x();
    double y = ray.origin().y() + t * ray.direction().y();

    if (m_X0 > x || m_X1 < x || m_Y0 > y || m_Y1 < y)
        return false;


    record.t = t;
    record.hitPoint = ray.at(record.t);
    record.materialPtr = m_MaterialPtr;
    Vector3 normalVector = Vector3(0, 0, 1);
    record.setFaceNormal(ray, record.normalVector);

    record.u = (x - m_X0) / (m_X1 - m_X0);
    record.v = (y - m_Y0) / (m_Y1 - m_Y0);

    record.u = fmod(x, 1);
    record.v = fmod(y, 1);

    return true;
}

bool XYPlane::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
    boundingBox = AABB(Point3(m_X0, m_Y0, m_K - 0.0001), Point3(m_X1, m_Y1, m_K + 0.0001));
    return true;
}



XZPlane::XZPlane(double x0, double x1, double z0, double z1, double k, const Material* material)
    : m_X0(x0), m_X1(x1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(material)
{
}

bool XZPlane::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    double t = (m_K - ray.origin().y()) / ray.direction().y();

    if (minT > t || maxT < t)
        return false;

    double x = ray.origin().x() + t * ray.direction().x();
    double z = ray.origin().z() + t * ray.direction().z();

    if (m_X0 > x || m_X1 < x || m_Z0 > z || m_Z1 < z)
        return false;

    record.t = t;
    record.hitPoint = ray.at(record.t);
    record.materialPtr = m_MaterialPtr;
    Vector3 normalVector = Vector3(0, 1, 0);
    record.setFaceNormal(ray, record.normalVector);

    record.u = (x - m_X0) / (m_X1 - m_X0);
    record.v = (z - m_Z0) / (m_Z1 - m_Z0);

    record.u = fmod(x, 1);
    record.v = fmod(z, 1);

    return true;
}

bool XZPlane::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
    boundingBox = AABB(Point3(m_X0, m_K - 0.0001, m_Z0), Point3(m_X1, m_K + 0.0001, m_Z1));
    return true;
}



YZPlane::YZPlane(double y0, double y1, double z0, double z1, double k, const Material* material)
    : m_Y0(y0), m_Y1(y1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(material)
{
}

bool YZPlane::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    double t = (m_K - ray.origin().x()) / ray.direction().x();

    if (minT > t || maxT < t)
        return false;

    double y = ray.origin().y() + t * ray.direction().y();
    double z = ray.origin().z() + t * ray.direction().z();

    if (m_Y0 > y || m_Y1 < y || m_Z0 > z || m_Z1 < z)
        return false;

    record.t = t;
    record.hitPoint = ray.at(record.t);
    record.materialPtr = m_MaterialPtr;
    Vector3 normalVector = Vector3(0, 0, 1);
    record.setFaceNormal(ray, record.normalVector);

    record.u = (y - m_Y0) / (m_Y1 - m_Y0);
    record.v = (z - m_Z0) / (m_Z1 - m_Z0);

    record.u = fmod(y, 1);
    record.v = fmod(z, 1);


    return true;
}

bool YZPlane::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
    boundingBox = AABB(Point3(m_K - 0.0001, m_Y0, m_Z0), Point3(m_K + 0.0001, m_Y1, m_Z1));
    return true;
}

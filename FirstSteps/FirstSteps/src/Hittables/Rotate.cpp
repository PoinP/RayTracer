#include "Rotate.h"
#include "../Utility/Utility.h"

#include "Translate.h"

Rotate::Rotate(std::shared_ptr<Hittable> object, double angle)
    : m_Object(object), m_Angle(degreesToRadians(angle)),
    m_CosTheta(cos(m_Angle)), m_SinTheta(sin(m_Angle))
{
   
}

bool Rotate::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    Vector3 rotatedOrigin = rotateInverse(ray.origin());
    Vector3 rotatedDir = rotateInverse(ray.direction());

    Ray rotatedRay = Ray(rotatedOrigin, rotatedDir, ray.time());

    if (!m_Object->isHit(rotatedRay, minT, maxT, record))
        return false;

    record.hitPoint = rotate(record.hitPoint);
    record.setFaceNormal(rotatedRay, rotate(record.normalVector));

    return true;
}

bool Rotate::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
    boundingBox = m_AABBox;
    return m_HasBox;
}

Point3 Rotate::getCenter() const
{
    if (!m_HasBox)
        return Point3(0, 0, 0);

    return (m_AABBox.min() + m_AABBox.max()) / 2;
}

Point3 Rotate::getOrigin() const
{
    if (!m_HasBox)
        return Point3(0, 0, 0);

    return m_AABBox.min();
}


RotateX::RotateX(std::shared_ptr<Hittable> object, double angle)
    : Rotate(object, angle)
{
    m_HasBox = m_Object->hasBoundingBox(0, 1, m_AABBox);

    if (m_HasBox)
    {
        Point3 min = Point3(INF, INF, INF);
        Point3 max = Point3(INF, INF, INF);

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int s = 0; s < 2; ++s)
                {
                    auto x = i * m_AABBox.max().x() + (1 - i) * m_AABBox.min().x();
                    auto y = j * m_AABBox.max().y() + (1 - j) * m_AABBox.min().y();
                    auto z = s * m_AABBox.max().z() + (1 - s) * m_AABBox.min().z();

                    auto rotatedBox = rotate(Point3(x, y, z));

                    for (int k = 0; k < 3; k++)
                    {
                        min[k] = fmin(min[k], rotatedBox[k]);
                        max[k] = fmax(max[k], rotatedBox[k]);
                    }
                }
            }
        }
    }
}

Vector3 RotateX::rotate(const Vector3& vector) const
{
    double x = vector.x();
    double y = vector.y() * m_CosTheta - vector.z() * m_SinTheta;
    double z = vector.y() * m_SinTheta + vector.z() * m_CosTheta;

    return Vector3(x, y, z);
}

Vector3 RotateX::rotateInverse(const Vector3& vector) const
{
    double x = vector.x();
    double y = vector.y() * m_CosTheta + vector.z() * m_SinTheta;
    double z = -vector.y() * m_SinTheta + vector.z() * m_CosTheta;

    return Vector3(x, y, z);
}



RotateY::RotateY(std::shared_ptr<Hittable> object, double angle)
    : Rotate(object, angle)
{
    m_HasBox = m_Object->hasBoundingBox(0, 1, m_AABBox);

    if (m_HasBox)
    {
        Point3 min = Point3(INF, INF, INF);
        Point3 max = Point3(INF, INF, INF);

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int s = 0; s < 2; ++s)
                {
                    auto x = i * m_AABBox.max().x() + (1 - i) * m_AABBox.min().x();
                    auto y = j * m_AABBox.max().y() + (1 - j) * m_AABBox.min().y();
                    auto z = s * m_AABBox.max().z() + (1 - s) * m_AABBox.min().z();

                    auto rotatedBox = rotate(Point3(x, y, z));

                    for (int k = 0; k < 3; k++)
                    {
                        min[k] = fmin(min[k], rotatedBox[k]);
                        max[k] = fmax(max[k], rotatedBox[k]);
                    }
                }
            }
        }
    }
}

Vector3 RotateY::rotate(const Vector3& vector) const
{
    double x = vector.x() * m_CosTheta + vector.z() * m_SinTheta;
    double y = vector.y();
    double z = -vector.x() * m_SinTheta + vector.z() * m_CosTheta;

    return Vector3(x, y, z);
}

Vector3 RotateY::rotateInverse(const Vector3& vector) const
{
    double x = vector.x() * m_CosTheta - vector.z() * m_SinTheta;
    double y = vector.y();
    double z = vector.x() * m_SinTheta + vector.z() * m_CosTheta;

    return Vector3(x, y, z);
}



RotateZ::RotateZ(std::shared_ptr<Hittable> object, double angle)
    : Rotate(object, angle)
{
}

Vector3 RotateZ::rotate(const Vector3& vector) const
{
    double x = vector.x() * m_CosTheta - vector.y() * m_SinTheta;
    double y = vector.x() * m_SinTheta + vector.y() * m_CosTheta;
    double z = vector.z();

    return Vector3(x, y, z);
}

Vector3 RotateZ::rotateInverse(const Vector3& vector) const
{
    double x = vector.x() * m_CosTheta + vector.y() * m_SinTheta;
    double y = -vector.x() * m_SinTheta + vector.y() * m_CosTheta;
    double z = vector.z();

    return Vector3(x, y, z);
}

void rotateX(std::shared_ptr<Hittable>& obj, double angle)
{
    Vector3 diff = obj->getOrigin() + obj->getCenter();

    translate(obj, -diff);
    obj = std::make_shared<RotateX>(obj, angle);
    translate(obj, diff);
}

void rotateY(std::shared_ptr<Hittable>& obj, double angle)
{
    Vector3 diff = obj->getOrigin() + obj->getCenter();

    translate(obj, -diff);
    obj = std::make_shared<RotateY>(obj, angle);
    translate(obj, diff);
}

void rotateZ(std::shared_ptr<Hittable>& obj, double angle)
{
    Vector3 diff = obj->getOrigin() + obj->getCenter();

    translate(obj, -diff);
    obj = std::make_shared<RotateZ>(obj, angle);
    translate(obj, diff);
}

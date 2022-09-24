#include "Translate.h"

#include "../Core/Ray.h"

Translate::Translate(const std::shared_ptr<Hittable>& object, const Vector3& offset)
    : m_Object(object), m_Offset(offset)
{
}

bool Translate::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
    Ray offsetRay = Ray(ray.origin() - m_Offset, ray.direction(), ray.time());
    
    if (!m_Object->isHit(offsetRay, minT, maxT, record))
        return false;

    record.hitPoint += m_Offset;
    record.setFaceNormal(offsetRay, record.normalVector);

    return true;
}

bool Translate::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{    
    if (!m_Object->hasBoundingBox(time0, time1, boundingBox))
        return false;

    boundingBox = AABB(boundingBox.min() + m_Offset, boundingBox.max() + m_Offset);

    return true;
}

Point3 Translate::getCenter() const
{
    return m_Object->getCenter() + m_Offset;
}

Point3 Translate::getOrigin() const
{
    return m_Object->getOrigin() + m_Offset;
}

void translate(std::shared_ptr<Hittable>& obj, const Vector3& offset)
{
    obj = std::make_shared<Translate>(obj, offset);
}

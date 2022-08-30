#include "Metal.h"

#include "Utility.h"

Metal::Metal(const Color& albedo, double fuzz)
    : m_Albedo(albedo), m_Fuzz(fuzz < 1 ? fuzz : 1)
{
}

bool Metal::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const
{
    Vector3 reflected = reflect(unitVector(ray.direction()), record.normalVector);
    scatter = Ray(record.hitPoint, reflected + m_Fuzz * randomInUnitSphere());
    reduction = m_Albedo;
    return (dotProduct(scatter.direction(), record.normalVector));
}

#include "Diffuse.h"

Diffuse::Diffuse(const Color& albedo)
    : m_Albedo(albedo)
{}

bool Diffuse::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const
{
    Vector3 scatterDirection = record.normalVector + randomUnitVector();

    if (scatterDirection.nearZero())
        scatterDirection = record.normalVector;

    scatter = Ray(record.hitPoint, scatterDirection, ray.time());
    
    reduction = m_Albedo;
    return true;
}

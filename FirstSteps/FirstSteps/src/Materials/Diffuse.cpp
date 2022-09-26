#include "Diffuse.h"
#include "../Textures/SolidColor.h"

Diffuse::Diffuse(std::shared_ptr<Texture> albedo)
    : m_Albedo(albedo)
{}

Diffuse::Diffuse(const Color& color)
    : m_Albedo(new SolidColor(color))
{}

bool Diffuse::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const
{
    Vector3 scatterDirection = record.normalVector + randomUnitVector();

    if (scatterDirection.nearZero())
        scatterDirection = record.normalVector;

    scatter = Ray(record.hitPoint, scatterDirection, ray.time());
    
    reduction = m_Albedo->value(record.u, record.v, record.hitPoint);
    return true;
}

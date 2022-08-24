#include "Dielectric.h"

#include "Utility.h"

Dielectric::Dielectric(double refractiveIndex)
    : m_RefractiveIndex(refractiveIndex)
{
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const
{
    const double airRefractionIndex = 1.003;

    double refrRatio = record.frontFacing ? (airRefractionIndex / m_RefractiveIndex) : (m_RefractiveIndex / airRefractionIndex);

    Vector3 unitDirectionVector = unitVector(ray.direction());
    const double cosTheta = fmin(dotProduct(-unitDirectionVector, record.normalVector), 1.0);
    const double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    Vector3 scatterDirection;

    if (refrRatio * sinTheta > 1.0 || reflectance(cosTheta, refrRatio) > randomDouble())
        scatterDirection = reflect(unitDirectionVector, record.normalVector);
    else
        scatterDirection = refract(unitDirectionVector, record.normalVector, refrRatio);

    scatteredRay = Ray(record.hitPoint, scatterDirection);
    reduction = Color(1.0, 1.0, 1.0);
    return true;
}

double Dielectric::reflectance(double cosTheta, double refrIndex) const
{
    const double airRefractionIndex = 1.003;

    double reflCoeff = (airRefractionIndex - refrIndex) / (airRefractionIndex + refrIndex);
    reflCoeff *= reflCoeff;
    return reflCoeff + (1 - reflCoeff) * pow((1 - cosTheta), 5);
}

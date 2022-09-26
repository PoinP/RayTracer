#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(const std::shared_ptr<Texture>& emitter, double intensity)
	: m_Emmiter(emitter), m_Intensity(intensity)
{
}

DiffuseLight::DiffuseLight(const Color& emitter, double intensity)
	: m_Emmiter(std::make_shared<SolidColor>(emitter)), m_Intensity(intensity > 1 ? 1 : intensity)
{
}

bool DiffuseLight::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const
{
	return false;
}

Color DiffuseLight::emit(double u, double v, const Point3& p) const
{
	return m_Emmiter->value(u, v, p) * m_Intensity;
}

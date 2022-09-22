#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(const Texture* emitter)
	: m_Emmiter(emitter)
{
}

DiffuseLight::DiffuseLight(const std::shared_ptr<Texture>& emitter)
	: m_Emmiter(emitter)
{
}

DiffuseLight::DiffuseLight(const SolidColor& emitter)
	: m_Emmiter(std::make_shared<SolidColor>(emitter))
{
}

DiffuseLight::DiffuseLight(const Color& emitter)
	: m_Emmiter(std::make_shared<SolidColor>(emitter))
{
}

bool DiffuseLight::scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const
{
	return false;
}

Color DiffuseLight::emit(double u, double v, const Point3& p) const
{
	return m_Emmiter->value(u, v, p);
}

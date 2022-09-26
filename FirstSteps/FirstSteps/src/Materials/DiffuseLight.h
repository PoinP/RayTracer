#ifndef DIFFUSE_LIGHT_H

#define DIFFUSE_LIGHT_H

#include "Material.h"
#include "../Textures/SolidColor.h"

#include <memory>

class DiffuseLight : public Material
{
public:
	DiffuseLight(const std::shared_ptr<Texture>& emitter, double intensity = 1);
	DiffuseLight(const Color& emitter, double intensity = 1);

	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const override;
	virtual Color emit(double u, double v, const Point3& p) const override;

private:
	std::shared_ptr<const Texture> m_Emmiter;
	double m_Intensity;
};

#endif // !DIFFUSE_LIGHT_H
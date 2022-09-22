#ifndef DIFFUSE_LIGHT_H

#define DIFFUSE_LIGHT_H

#include "Material.h"
#include "../Textures/SolidColor.h"

#include <memory>

class DiffuseLight : public Material
{
public:
	DiffuseLight(const Texture* emitter);
	DiffuseLight(const std::shared_ptr<Texture>& emitter);
	DiffuseLight(const SolidColor& emitter);
	DiffuseLight(const Color& emitter);

	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const override;
	virtual Color emit(double u, double v, const Point3& p) const override;

private:
	std::shared_ptr<const Texture> m_Emmiter;
};

#endif // !DIFFUSE_LIGHT_H
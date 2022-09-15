#ifndef METAL_H

#define METAL_H

#include "Material.h"
#include "../Hittables/Hittable.h"

class Metal : public Material
{
public:
	Metal(const Color& albedo, double fuzz);
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const override;
private:
	Color m_Albedo;
	double m_Fuzz;
};

#endif // !METAL_H
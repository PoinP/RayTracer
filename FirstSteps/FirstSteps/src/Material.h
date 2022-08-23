#ifndef MATERIAL_H

#define MATERIAL_H

#include "Hittable.h"
#include "Ray.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const = 0;
};

#endif // !MATERIAL_H
#ifndef MATERIAL_H

#define MATERIAL_H

#include "../Hittables/Hittable.h"
#include "../Core/Ray.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const = 0;
	virtual bool transmit() const;
};

#endif // !MATERIAL_H
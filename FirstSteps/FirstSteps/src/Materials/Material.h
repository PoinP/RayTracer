#ifndef MATERIAL_H

#define MATERIAL_H

#include "../Hittables/Hittable.h"
#include "../Core/Ray.h"
#include "../Core/Vector3.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const = 0;
	virtual Color emit(double u, double v, const Point3& p) const { return Color(0.0, 0.0, 0.0); }
	virtual bool transmit() const;
	virtual ~Material() {}
};

#endif // !MATERIAL_H
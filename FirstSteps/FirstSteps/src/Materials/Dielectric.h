#ifndef DIELECTRIC_H

#define DIELECTRIC

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(double refractiveIndex);

	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatteredRay) const;
	virtual bool transmit() const override;

private:
	double m_RefractiveIndex;

	double reflectance(double cosTheta, double incidentIndex) const;
};

#endif // !DIELECTRIC_H
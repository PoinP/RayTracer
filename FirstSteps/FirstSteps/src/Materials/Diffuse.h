#ifndef DIFFUSE_H

#define DIFFSUE_H

#include "Material.h"
#include "../Utility/Utility.h"

class Diffuse : public Material
{
public:
	Diffuse(const Color& albedo);
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const override;
private:
	Color m_Albedo;
};

#endif // !DIFFUSE_H
#ifndef DIFFUSE_H

#define DIFFSUE_H

#include "Material.h"
#include "../Textures/Texture.h"
#include "../Utility/Utility.h"

class Diffuse : public Material
{
public:
	Diffuse(const Texture* albedo);
	Diffuse(const Color& color);
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const override;

private:
	const Texture* m_Albedo;
};

#endif // !DIFFUSE_H
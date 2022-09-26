#ifndef DIFFUSE_H

#define DIFFSUE_H

#include "Material.h"
#include "../Textures/Texture.h"
#include "../Utility/Utility.h"

#include <memory>

class Diffuse : public Material
{
public:
	Diffuse(std::shared_ptr<Texture> albedo);
	Diffuse(const Color& color);
	virtual bool scatter(const Ray& ray, const HitRecord& record, Color& reduction, Ray& scatter) const override;

private:
	const std::shared_ptr<Texture> m_Albedo;
};

#endif // !DIFFUSE_H
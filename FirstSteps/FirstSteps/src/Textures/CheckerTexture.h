#ifndef CHECKER_TEXTURE_H

#define CHECKER_TEXTURE_H

#include "Texture.h"
#include "SolidColor.h"

#include <memory>

class CheckerTexture : public Texture
{
public:
	CheckerTexture();
	CheckerTexture(const Texture* even, const Texture* odd);
	CheckerTexture(const std::shared_ptr<Texture>& even, const std::shared_ptr<Texture>& odd);
	CheckerTexture(const SolidColor* firstColor, const SolidColor* secondColor);
	CheckerTexture(const Color& firstColor, const Color& secondColor);

	virtual Color value(double u, double v, const Point3& p) const override;

private:
	std::shared_ptr<const Texture> m_Even;
	std::shared_ptr<const Texture> m_Odd;
};

#endif // !CHECKER_TEXTURE

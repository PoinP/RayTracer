#ifndef CHECKER_TEXTURE_H

#define CHECKER_TEXTURE_H

#include "Texture.h"
#include "SolidColor.h"

class CheckerTexture : public Texture
{
public:
	CheckerTexture();
	CheckerTexture(const Texture* even, const Texture* odd);
	CheckerTexture(const SolidColor& firstColor, const SolidColor& secondColor);

	virtual Color value(double u, double v, const Point3& p) const override;

private:
	const Texture* m_Even;
	const Texture* m_Odd;
};

#endif // !CHECKER_TEXTURE

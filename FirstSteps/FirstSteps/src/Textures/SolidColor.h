#ifndef SOLID_COLOR_H

#define SOLID_COLOR_H

#include "Texture.h"

class SolidColor : public Texture
{
public:
	SolidColor();
	SolidColor(const Color& color);
	SolidColor(double r, double g, double b);

	virtual Color value(double u, double v, const Point3& p) const override;

private:
	Color m_ColorValue;
};

#endif // !SOLID_COLOR_H

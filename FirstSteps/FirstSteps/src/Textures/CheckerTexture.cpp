#include "CheckerTexture.h"

CheckerTexture::CheckerTexture()
    : CheckerTexture(std::make_shared<SolidColor>(0.9, 0.0, 0.9), std::make_shared<SolidColor>(0.0, 0.0, 0.0))
{
}

CheckerTexture::CheckerTexture(const std::shared_ptr<Texture>& even, const std::shared_ptr<Texture>& odd)
    : m_Even(even), m_Odd(odd)
{
}

CheckerTexture::CheckerTexture(const Color& firstColor, const Color& secondColor)
    : CheckerTexture(std::make_shared<SolidColor>(firstColor.x(), firstColor.y(), firstColor.z()), 
        std::make_shared<SolidColor>(firstColor.x(), firstColor.y(), firstColor.z()))
{
}

Color CheckerTexture::value(double u, double v, const Point3& p) const
{
    const int width = 256;
    const int height = 256;

    double u2 = floor(u * width);
    double v2 = floor(v * height);

    if (int(u2 + v2) % 2 == 0)
        return m_Even->value(u2, v2, p);
    else
        return m_Odd->value(u2, v2, p);
}

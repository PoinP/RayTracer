#include "CheckerTexture.h"

CheckerTexture::CheckerTexture()
    : CheckerTexture(new SolidColor(0.2, 0.3, 0.1), new SolidColor(0.9, 0.9, 0.9))
{
}

CheckerTexture::CheckerTexture(const Texture* even, const Texture* odd)
    : m_Even(even), m_Odd(odd)
{
}

CheckerTexture::CheckerTexture(const SolidColor& firstColor, const SolidColor& secondColor)
    : m_Even(&firstColor), m_Odd(&secondColor)
{
}

Color CheckerTexture::value(double u, double v, const Point3& p) const
{
    const int width = 16;
    const int height = 9;

    double u2 = floor(u * width);
    double v2 = floor(v * height);

    if (int(u2 + v2) % 2 == 0)
        return m_Even->value(u2, v2, p);
    else
        return m_Odd->value(u2, v2, p);
}

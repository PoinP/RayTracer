#include "SolidColor.h"

SolidColor::SolidColor()
    : m_ColorValue(Color(0, 0, 0))
{
}

SolidColor::SolidColor(const Color& color)
    : m_ColorValue(color)
{
}

SolidColor::SolidColor(double r, double g, double b)
    : m_ColorValue(Color(r, g, b))
{
    if (r > 1.0 || g > 1.0 || b > 1.0)
        m_ColorValue = Color(1.0, 1.0, 1.0);
}

Color SolidColor::value(double u, double v, const Point3& p) const
{
    return m_ColorValue;
}

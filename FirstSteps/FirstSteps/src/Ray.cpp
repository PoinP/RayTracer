#include "Ray.h"

#include "Materials.h"

Ray::Ray()
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : m_Origin(origin), m_Direction(direction)
{
}

const Vector3& Ray::origin() const
{
    return m_Origin;
}

const Vector3& Ray::direction() const
{
    return m_Direction;
}

Vector3 Ray::at(double scalar) const
{
    return m_Origin + (scalar * m_Direction);
}

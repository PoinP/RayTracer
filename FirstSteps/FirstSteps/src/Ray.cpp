#include "Ray.h"

#include "Materials.h"

Ray::Ray()
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction, double time)
    : m_Origin(origin), m_Direction(direction), m_Time(time)
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

const double& Ray::time() const
{
    return m_Time;
}

Vector3 Ray::at(double scalar) const
{
    return m_Origin + (scalar * m_Direction);
}

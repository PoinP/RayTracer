#include "Camera.h"

Camera::Camera()
{
    double aspectRatio = 16.0 / 9.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLength = 1.0;

    m_Origin = Point3(0, 0, 0);
    m_HorizontalPlane = Vector3(viewportWidth, 0, 0);
    m_VerticalPlane = Vector3(0, viewportHeight, 0);
    m_UpperLeftCorner = m_Origin - m_HorizontalPlane * 0.5 + m_VerticalPlane * 0.5 - Vector3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) const
{
    return Ray(m_Origin, m_UpperLeftCorner + u * m_HorizontalPlane - v * m_VerticalPlane - m_Origin);
}

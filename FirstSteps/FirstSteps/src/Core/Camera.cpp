#include "Camera.h"

#include "../Utility/Utility.h"

Camera::Camera(const Point3& lookFrom, const Point3& lookAt, const Vector3& vUp, double aspectRatio, double verticalFov, double aperature, double focusDistance, double time0, double time1)
{
    double theta = degreesToRadians(verticalFov);
    double h = tan(theta * 0.5);
    double viewportHeight = 2.0 * h;
    double viewportWidth = viewportHeight * aspectRatio;

    m_W = unitVector(lookFrom - lookAt);
    m_U = unitVector(crossProduct(vUp, m_W));
    m_V = crossProduct(m_W, m_U);

    m_Origin = lookFrom;
    m_HorizontalPlane = focusDistance * viewportWidth * m_U;
    m_VerticalPlane = focusDistance * viewportHeight * m_V;
    m_UpperLeftCorner = m_Origin - m_HorizontalPlane * 0.5 + m_VerticalPlane * 0.5 - focusDistance * m_W;

    m_LensRadius = aperature / 2;

    m_Time0 = time0;
    m_Time1 = time1;
}

Camera::Camera(const CameraOptions& options)
    : Camera(options.lookFrom, options.lookAt, options.vUp, options.aspectRatio, options.verticalFOV, options.aperature, options.focusDistance)
{}

Ray Camera::getRay(double s, double t) const
{
    Vector3 randomStart = m_LensRadius * randomInUnitDisk();
    Vector3 offset = m_U * randomStart.x() + m_V * randomStart.y();

    return Ray(m_Origin + offset, m_UpperLeftCorner + s * m_HorizontalPlane - t * m_VerticalPlane - m_Origin - offset, randomDouble(m_Time0, m_Time1));
}
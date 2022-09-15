#ifndef CAMERA_H

#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

struct CameraOptions
{
	Point3 lookAt;
	Point3 lookFrom;
	Point3 vUp;
	double aspectRatio;
	double verticalFOV;
	double aperature;
	double focusDistance;
	double time0 = 0;
	double time1 = 1;
};

class Camera
{
public:
	Camera(const Point3& lookFrom, const Point3& lookAt, const Vector3& vUp, double aspectRatio, double verticalFov, double aperature, double focusDistance, double time0 = 0, double time1 = 1);
	Camera(const CameraOptions& options);

	Ray getRay(double u, double v) const;

private:
	Point3 m_HorizontalPlane;
	Point3 m_VerticalPlane;

	Point3 m_Origin;
	Point3 m_UpperLeftCorner;

	Vector3 m_U, m_V, m_W;

	double m_LensRadius;
	double m_Time0, m_Time1;
};

#endif // !CAMERA_H
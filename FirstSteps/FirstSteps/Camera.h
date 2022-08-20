#ifndef CAMERA_H

#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
	Camera();

	Ray getRay(double u, double v) const;
private:
	Point3 m_HorizontalPlane;
	Point3 m_VerticalPlane;

	Point3 m_Origin;
	Point3 m_UpperLeftCorner;
};

#endif // !CAMERA_H
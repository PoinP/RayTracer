// This is most likely a shitty way of doing it:
// Basically I need to use rayColor in Main.cpp and Worker.cpp
// And this is the most hacky way I could think of doing it
// Without putting it inside another class (ex. Ray)

#ifndef RAY_COLOR_H

#define RAY_COLOR_H

#include "Ray.h"
#include "Color.h"
#include"LightSource.h"

#include "../Hittables/HittableList.h"
#include "../Materials/Material.h"

inline Color rayColor(const Ray& ray, const HittableList& world, unsigned int depth)
{
	HitRecord record;

	if (depth <= 0) 
		return Color(0, 0, 0);

	const LightSource light = LightSource(Point3(0.0, 16, 0), 0.4);

	if (world.isHit(ray, 0.001, INF, record))
	{
		Ray scatteredRay;
		Color reduction;

		if (record.materialPtr->scatter(ray, record, reduction, scatteredRay))
		{
			/*if (light.isInShadow(scatteredRay, record, world))
				return Color(0.0, 0.0, 0.0);*/

			return reduction * rayColor(scatteredRay, world, depth - 1);
		}

		return Color(0, 0, 0);
	}

	Vector3 unitDirecion = unitVector(ray.direction());
	double t = 0.5 * (unitDirecion.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0);
}

inline Color rayColor(const Ray& ray, const Color& background, const HittableList& world, unsigned int depth)
{
	HitRecord record;

	if (depth <= 0)
		return Color(0, 0, 0);

	if (!world.isHit(ray, 0.001, INF, record))
		return background;

	Ray scatteredRay;
	Color reduction;
	Color emittedColor = record.materialPtr->emit(record.u, record.v, record.hitPoint);

	if (!record.materialPtr->scatter(ray, record, reduction, scatteredRay))
		return emittedColor;

	return emittedColor + reduction * rayColor(scatteredRay, background, world, depth - 1);
}

#endif // !RAY_COLOR_H


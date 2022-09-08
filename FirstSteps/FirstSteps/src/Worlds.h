#ifndef WORLDS_H

#define WORLDS_H

#include "Sphere.h"
#include "MovingSphere.h"

inline HittableList createWorld()
{
	Material* sunMaterial = new Diffuse(Color(0.9, 0.7, 0.4));

	Material* materialGround = new Diffuse(Color(0.8, 0.8, 0.0));
	//Material* materialCenter = new Diffuse(Color(0.1, 0.2, 0.5));
	Material* materialCenter = new Diffuse(Color(1.0, 0.2, 0.5));
	Material* materialLeft = new Dielectric(1.2);
	Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.0);
	//Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.9);

	HittableList objects;
	//objects.add(new Sphere(Point3(0.0, 2, 2), 1.5, sunMaterial));
	//objects.add(new Sphere(Point3(0.0, 2, -1), 0.5, sunMaterial));

	objects.add(new Sphere(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	//objects.add(new Sphere(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	objects.add(new MovingSphere(Point3(0.0, 0.0, -1.0), Point3(0.0, 0.3, -1.0), 0.5, 1.0, 0.2, materialCenter));
	objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	//objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), -0.45, materialLeft));
	objects.add(new Sphere(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

	return objects;
}

inline HittableList generateRandomWorld()
{
	HittableList world;
	Material* groundMaterial = new Diffuse(Color(0.5, 0.5, 0.5));
	world.add(new Sphere(Point3(0, -1000, 0), 1000, groundMaterial));

	for (int i = -11; i < 11; ++i)
	{
		for (int j = -11; j < 11; ++j)
		{
			double randomNum = randomDouble();
			Point3 center = Point3(i + 0.9 * randomDouble(), 0.2, j + 0.9 * randomDouble());

			if ((center - Point3(4, 0.2, 0)).length() > 1)
			{
				if (randomNum < 0.5)
				{
					Color color = Color::random() * Color::random();
					Material* material = new Diffuse(color);
					world.add(new Sphere(center, 0.2, material));
				}
				else if (randomNum < 0.8)
				{
					Color color = Color::random() * Color::random();
					Material* material = new Metal(color, randomDouble());
					world.add(new Sphere(center, 0.2, material));
				}
				else
				{
					Material* material = new Dielectric(1 + randomDouble() * 0.6);
					world.add(new Sphere(center, 0.2, material));
				}
			}
		}
	}

	Material* dielectric = new Dielectric(1.5);
	Material* diffuse = new Diffuse(Color(0.53, 0.81, 0.94));
	Material* metal = new Metal(Color(0.7, 0.6, 0.5), 0.0);

	world.add(new Sphere(Point3(0.0, 1.0, 0.0), 1.0, dielectric));
	world.add(new Sphere(Point3(-4.0, 1.0, 0.0), 1.0, diffuse));
	world.add(new Sphere(Point3(4.0, 1.0, 0.0), 1.0, metal));

	return world;
}

#endif // !WORLDS_H


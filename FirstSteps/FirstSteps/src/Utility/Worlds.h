#ifndef WORLDS_H

#define WORLDS_H

#include "../Hittables/Hittables.h"
#include "../Materials/Materials.h"
#include "../Textures/CheckerTexture.h"
#include "../Textures/ImageTexture.h"

inline HittableList createWorld()
{
	Material* sunMaterial = new Diffuse(Color(0.9, 0.7, 0.4));

	Texture* texture = new CheckerTexture();
	//Material* materialGround = new Diffuse(texture);
	//Material* materialGround = new Diffuse(Color(0.8, 0.8, 0.0));
	Material* materialGround = new Diffuse(texture);
	Material* materialCenter = new Diffuse(Color(0.1, 0.2, 0.5));
	//Material* materialCenter = new Diffuse(Color(1.0, 0.2, 0.5));
	//Material* materialLeft = new Dielectric(1.2);

	Texture* texture2 = new ImageTexture("textures/earth.ppm");


	Material* materialLeft = new Diffuse(texture2);
	Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.0);
	//Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.9);

	HittableList objects;
	//objects.add(new Sphere(Point3(0.0, 2, 2), 1.5, sunMaterial));
	//objects.add(new Sphere(Point3(0.0, 2, -1), 0.5, sunMaterial));

	//objects.add(new Sphere(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	objects.add(new Sphere(Point3(0.0, -15.5, -1.0), 15.0, materialGround));
	//objects.add(new Sphere(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	objects.add(new MovingSphere(Point3(0.0, 0.0, -1.0), Point3(0.0, 0.3, -1.0), 0.5, 1.0, 0.2, materialCenter));
	objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	//objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), -0.45, materialLeft));
	objects.add(new Sphere(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

	return objects;
}

inline HittableList createWorld2()
{
	Texture* texture = new CheckerTexture();
	Material* materialGround = new Diffuse(texture);

	HittableList objects;

	objects.add(new Sphere(Point3(0.0, 0.0, 0.0), 1, materialGround));

	return objects;
}

inline HittableList createWorld3()
{
	Material* earth = new Diffuse(new ImageTexture("textures/earth.ppm"));
	Material* mars = new Diffuse(new ImageTexture("textures/mars.ppm"));
	Material* moon = new Diffuse(new ImageTexture("textures/moon.ppm"));

	HittableList objects;

	objects.add(new Sphere(Point3(0.0, 0.0, 0.0), 1, earth));
	objects.add(new Sphere(Point3(1.0, 1.2, -2.0), 0.7, mars));
	objects.add(new Sphere(Point3(-0.8, -0.9, -1.0), 0.6, moon));

	return objects;
}

inline HittableList createWorld4()
{
	Material* earth = new Diffuse(new ImageTexture("textures/stofi.ppm"));
	Material* mars = new Diffuse(new ImageTexture("textures/mars.ppm"));
	Material* moon = new Diffuse(new ImageTexture("textures/moon.ppm"));

	HittableList objects;

	objects.add(new Sphere(Point3(0.0, 0.0, 0.0), 1, earth));
	objects.add(new Sphere(Point3(1.0, 1.3, -2.0), 0.7, mars));
	objects.add(new Sphere(Point3(-0.8, -0.9, -1.0), 0.6, moon));

	return objects;
}

inline HittableList generateRandomWorld()
{
	HittableList world;
	Material* groundMaterial = new Diffuse(Color(0.5, 0.5, 0.5));
	world.add(new Sphere(Point3(0, -1000, 0), 1000, groundMaterial));

	HittableList miniSpheres;
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
					miniSpheres.add(new Sphere(center, 0.2, material));
				}
				else if (randomNum < 0.8)
				{
					Color color = Color::random() * Color::random();
					Material* material = new Metal(color, randomDouble());
					miniSpheres.add(new Sphere(center, 0.2, material));
				}
				else
				{
					Material* material = new Dielectric(1 + randomDouble() * 0.6);
					miniSpheres.add(new Sphere(center, 0.2, material));
				}
			}
		}
	}

	world.add(new BVH(miniSpheres, 0, 0));

	Material* dielectric = new Dielectric(1.5);
	Material* diffuse = new Diffuse(Color(0.53, 0.81, 0.94));
	Material* metal = new Metal(Color(0.7, 0.6, 0.5), 0.0);

	world.add(new Sphere(Point3(0.0, 1.0, 0.0), 1.0, dielectric));
	world.add(new Sphere(Point3(-4.0, 1.0, 0.0), 1.0, diffuse));
	world.add(new Sphere(Point3(4.0, 1.0, 0.0), 1.0, metal));

	return world;
}

#endif // !WORLDS_H


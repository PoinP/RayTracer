#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "Material.h"
#include "Diffuse.h"
#include "Metal.h"
#include "Dielectric.h"

void createImage(std::ofstream& output, int width, int height);
Color rayColor(const Ray& ray, const HittableList& world, unsigned int depth);
double sphereHit(const Vector3& center, double radius, const Ray& ray);
HittableList createWorld();

int main()
{
	const double aspectRatio = 16.0 / 9.0;
	const int width = 400;
	const int height = static_cast<int>(width / aspectRatio);

	std::ofstream stream("image.ppm");
	createImage(stream, width, height);
	stream.close();
};

void createImage(std::ofstream& output, int width, int height)
{
	Camera cam;
	const unsigned int sampleCount = 100;
	const unsigned int maxDepth = 50;

	output << "P3" << std::endl;
	output << width << " " << height << std::endl;
	output << "255" << std::endl;

	HittableList world = createWorld();

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Color pixel;

			for (int s = 0; s < sampleCount; ++s)
			{
				double u = (j + randomDouble()) / ((double)width - 1);
				double v = (i + randomDouble()) / ((double)height - 1);

				Ray ray = cam.getRay(u, v);

				pixel += rayColor(ray, world, maxDepth);
			}

			writeColor(output, pixel, sampleCount);
		}

		int percentage = (int)((i / ((double)height - 1)) * 100);
		std::cout << "\rPercantage: " << percentage << std::flush;
	}

	std::cout << "\nDone!" << std::endl;
}

Color rayColor(const Ray& ray, const HittableList& world, unsigned int depth)
{
	HitRecord record;

	if (depth <= 0) return Color(0, 0, 0);

	if (world.isHit(ray, 0.001, INF, record))
	{
		Ray scatteredRay;
		Color reduction;

		if (record.materialPtr->scatter(ray, record, reduction, scatteredRay))
			return reduction * rayColor(scatteredRay, world, depth - 1);
		return Color(0, 0, 0);
	}

	Vector3 unitDirecion = unitVector(ray.direction());
	double t = 0.5 * (unitDirecion.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0);
}

HittableList createWorld()
{
	Material* materialGround = new Diffuse(Color(0.8, 0.8, 0.0));
	Material* materialCenter = new Diffuse(Color(0.7, 0.3, 0.3));
	Material* materialLeft = new Metal(Color(0.8, 0.8, 0.8), 0.2);
	Material* materialRight = new Dielectric(1.33);
	//Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.9);

	HittableList objects;
	objects.add(new Sphere(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	objects.add(new Sphere(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	objects.add(new Sphere(Point3(1.0, 0.0, -1.0), 0.5, materialRight));
	objects.add(new Sphere(Point3(1.0, 0.0, -1.0), -0.4, materialRight));

	return objects;
}
#ifndef WORLDS_H

#define WORLDS_H

#include "../Hittables/Hittables.h"
#include "../Materials/Materials.h"
#include "../Textures/CheckerTexture.h"
#include "../Textures/ImageTexture.h"

inline HittableList threeSpheres()
{
	// Materials
	auto materialGround = std::make_shared<Diffuse>(std::make_shared<CheckerTexture>());
	auto materialLeft = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/earth.ppm"));
	auto materialCenter = std::make_shared<Diffuse>(Color(0.1, 0.2, 0.5));
	auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

	auto negX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negx.ppm"), 0.7);
	auto negY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negy.ppm"), 0.7);
	auto negZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negz.ppm"), 0.7);
	auto posX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posx.ppm"), 0.7);
	auto posY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posy.ppm"), 0.7);
	auto posZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posz.ppm"), 0.7);

	std::vector<std::shared_ptr<Material>> cubemap = { negX, negY, negZ, posX, posY, posZ };

	HittableList world;

	// Objects in world
	world.add(std::make_shared<Box>(Point3(-2000, -2000, -2000), Vector3(4000, 4000, 4000), cubemap));
	world.add(std::make_shared<XZPlane>(-100, 100, -100, 100, -0.5, materialGround));
	world.add(std::make_shared<MovingSphere>(Point3(0.0, 0.0, -1.0), Point3(0.0, 0.3, -1.0), 0.5, 1.0, 0.2, materialCenter));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

	return world;
}

inline HittableList threePlanets()
{
	// Materials

	// Cubemap (Skybox)
	auto negX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negx.ppm"), 0.15);
	auto negY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negy.ppm"), 0.15);
	auto negZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negz.ppm"), 0.15);
	auto posX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posx.ppm"), 0.15);
	auto posY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posy.ppm"), 0.15);
	auto posZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posz.ppm"), 0.15);

	std::vector<std::shared_ptr<Material>> cubemap = { negX, negY, negZ, posX, posY, posZ };

	auto earth = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/earth.ppm"));
	auto mars = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/mars.ppm"));
	auto moon = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/moon.ppm"));
	auto light = std::make_shared<DiffuseLight>(Color(16, 16, 16));

	HittableList objects;

	// Objects
	std::shared_ptr<Hittable> lightSource = std::make_shared<XZPlane>(0, 2, 0, 2, 5, light);
	rotateX(lightSource, -35);

	objects.add(lightSource);
	objects.add(std::make_shared<Box>(Point3(-50, -50, -50), Vector3(100, 100, 100), cubemap));
	objects.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1, earth));
	objects.add(std::make_shared<Sphere>(Point3(1.0, 1.2, -2.0), 0.7, mars));
	objects.add(std::make_shared<Sphere>(Point3(-0.8, -0.9, -1.0), 0.6, moon));

	return objects;
}

inline HittableList cornellBox()
{
	HittableList objects;

	// Materials
	auto red = std::make_shared<Diffuse>(Color(0.65, 0.05, 0.05));
	auto white = std::make_shared<Diffuse>(Color(0.73, 0.73, 0.73));
	auto green = std::make_shared<Diffuse>(Color(0.12, 0.45, 0.15));
	auto light = std::make_shared<DiffuseLight>(Color(14, 14, 14));

	auto glass = std::make_shared<Dielectric>(1.60);

	// Cornell Box Walls(without the front one)
	objects.add(std::make_shared<YZPlane>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<YZPlane>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<XZPlane>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<XZPlane>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<XYPlane>(0, 555, 0, 555, 555, white));

	// Cornell Box Light Source
	objects.add(std::make_shared<XZPlane>(213, 343, 227, 332, 554, light));

	// Objects inside the Cornell Box
	std::shared_ptr<Hittable> smallBox = std::make_shared<Box>(Point3(110.0, 0.0, 65.0), Point3(165.0, 165.0, 165.0), white);
	std::shared_ptr<Hittable> bigBox = std::make_shared<Box>(Point3(285.0, 0.0, 295.0), Point3(165.0, 330.0, 165.0), white);
	std::shared_ptr<Hittable> glassSphere = std::make_shared<Sphere>(Point3(182.0, 245.0, 125.5), 80, glass);

	rotateY(smallBox, -18);
	rotateY(bigBox, 15);

	objects.add(smallBox);
	objects.add(bigBox);
	objects.add(glassSphere);

	return objects;
}

#include "../Hittables/Rotate.h"

inline HittableList sphereInJapan()
{
	HittableList objects;

	// Cubemap load (TODO: try using "boost::iostreams::mapped_file" for faster image loading)
	std::shared_ptr<Material> negX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/negx.ppm"), 0.4);
	std::shared_ptr<Material> negY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/negy.ppm"), 0.4);
	std::shared_ptr<Material> negZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/negz.ppm"), 0.4);
	std::shared_ptr<Material> posX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/posx.ppm"), 0.4);
	std::shared_ptr<Material> posY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/posy.ppm"), 0.4);
	std::shared_ptr<Material> posZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Yokahoma/posz.ppm"), 0.4);

	// Create the skybox
	std::vector<std::shared_ptr<Material>> cubemap = { negX, negY, negZ, posX, posY, posZ };
	std::shared_ptr<Hittable> skybox = std::make_shared<Box>(Point3(-300, -300, -300), Point3(600, 600, 600), cubemap);

	// Create the mirror ball
	std::shared_ptr<Material> mirror = std::make_shared<Metal>(Color(1, 1, 1), 0.01);
	std::shared_ptr<Hittable> ball = std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 50, mirror);

	objects.add(skybox);
	objects.add(ball);

	return objects;
}

// ------------- TODO: ADD SPACE TEXTURES ------------------


	//CameraOptions camOptions = {
	//Point3(-450.0, 200.0, 1000.0),
	//Point3(-550, 300, 600),
	//Point3(0.0, 1.0, 0.0),
	//aspectRatio,
	//25,
	//0,
	//(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	//};


//inline HittableList space()
//{
//	HittableList objects;
//
//	auto negX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negx.ppm"), 0.15);
//	auto negY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negy.ppm"), 0.15);
//	auto negZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/negz.ppm"), 0.15);
//	auto posX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posx.ppm"), 0.15);
//	auto posY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posy.ppm"), 0.15);
//	auto posZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Space/posz.ppm"), 0.15);
//
//	std::vector<std::shared_ptr<Material>> cubemap = { negX, negY, negZ, posX, posY, posZ };
//
//	std::shared_ptr<Hittable> skybox = std::make_shared<Box>(Point3(-1500, -1000, -3000), Point3(3000, 2000, 6000), cubemap);
//
//	auto sunLight = std::make_shared<DiffuseLight>(Color(20, 15, 12));
//	std::shared_ptr<Material> sunMat = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/sun.ppm"), 1.5);
//	std::shared_ptr<Material> earthMat = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/earth_alt.ppm"));
//	std::shared_ptr<Material> moonMat = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/moon.ppm"));
//	std::shared_ptr<Material> venusMat = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/venus.ppm"));
//
//
//	std::shared_ptr<Hittable> sun = std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 400, sunMat);
//	std::shared_ptr<Hittable> lightOfSun = std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 450, sunLight);
//	std::shared_ptr<Hittable> venus = std::make_shared<Sphere>(Point3(-450.0, 200.0, 1000.0), 40, venusMat);
//	std::shared_ptr<Hittable> earth = std::make_shared<Sphere>(Point3(-120.0, 120.0, 1800.0), 70, earthMat);
//	std::shared_ptr<Hittable> moon = std::make_shared<Sphere>(Point3(-170.0, 80.0, 1620.0), 20, moonMat);
//
//	objects.add(skybox);
//	objects.add(sun);
//	objects.add(venus);
//	objects.add(earth);
//	objects.add(moon);
//
//	return objects;
//}


inline HittableList randomSpheres()
{
	HittableList world;

	// Cubemap (Skybox)
	auto negX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negx.ppm"), 0.7);
	auto negY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negy.ppm"), 0.7);
	auto negZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/negz.ppm"), 0.7);
	auto posX = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posx.ppm"), 0.7);
	auto posY = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posy.ppm"), 0.7);
	auto posZ = std::make_shared<DiffuseLight>(std::make_shared<ImageTexture>("textures/cubemaps/Sky/posz.ppm"), 0.7);

	std::vector<std::shared_ptr<Material>> cubemap = { negX, negY, negZ, posX, posY, posZ };

	world.add(std::make_shared<Box>(Point3(-2000, -2000, -2000), Vector3(4000, 4000, 4000), cubemap));

	auto groundMaterial = std::make_shared<Diffuse>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

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
					auto material = std::make_shared<Diffuse>(color);
					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material));
				}
				else if (randomNum < 0.8)
				{
					Color color = Color::random() * Color::random();
					auto material = std::make_shared<Metal>(color, randomDouble());
					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material));
				}
				else
				{
					auto material =std::make_shared<Dielectric>(1 + randomDouble() * 0.6);
					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material));
				}
			}
		}
	}

	world.add(std::make_shared<BVH>(miniSpheres, 0, 0));

	auto dielectric = std::make_shared<Dielectric>(1.5);
	auto diffuse = std::make_shared<Diffuse>(Color(0.53, 0.81, 0.94));
	auto metal = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);

	world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, dielectric));
	world.add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, diffuse));
	world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, metal));

	return world;
}

#endif // !WORLDS_H


#ifndef SCENES_H

#define SCENES_H

#include "Worlds.h"
#include "../Core/Camera.h"
#include "../Hittables/HittableList.h"

struct Scene
{
	CameraOptions cameraOptions;
	HittableList world;
};

Scene cornellBoxScene(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(278.0, 278.0, 0),
		Point3(278, 278, -800),
		Point3(0.0, 1.0, 0.0),
		aspectRatio,
		40,
		0,
		(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	HittableList world = cornellBox();

	return Scene{ camOptions, world };
}

Scene sphereInJapanScene(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(0.0, 0.0, 0.0),
		Point3(0, 70, -295),
		Point3(0.0, 1.0, 0.0),
		aspectRatio,
		40,
		0,
		(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	HittableList world = sphereInJapan();

	return Scene{ camOptions, world };
}

Scene randomWorldScene(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(0, 0, 0),
		Point3(13, 2, 3),
		Point3(0, 1 ,0),
		aspectRatio,
		30,
		0.1,
		10
	};

	HittableList world = randomSpheres();

	return Scene{ camOptions, world };
}

Scene threeSpheresScene(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(0.0, 0.0, -1.0),
		Point3(0.0, 1.5, 5.0),
		Point3(0.0, 1.0, 0.0),
		aspectRatio,
		40,
		0,
		(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	HittableList world = threeSpheres();

	return Scene{ camOptions, world };
}

Scene threePlanetsScene(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(0.0, 0.0, -1.0),
		Point3(0.0, 1.5, 10.0),
		Point3(0.0, 1.0, 0.0),
		aspectRatio,
		20,
		0,
		(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	HittableList world = threePlanets();

	return Scene{ camOptions, world };
}

// Still working on this, might scrap ti actually :((
Scene testCornellBox(double aspectRatio = 16 / 9)
{
	CameraOptions camOptions = {
		Point3(-500, -500, -500),
		Point3(-500, -500, -0.0001),
		Point3(0.0, 1.0, 0.0),
		aspectRatio,
		65,
		0,
		(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	HittableList world;

	auto red = std::make_shared<Diffuse>(Color(0.65, 0.05, 0.05));
	auto white = std::make_shared<DiffuseLight>(Color(0.73, 0.73, 0.73),0.4);
	auto green = std::make_shared<Diffuse>(Color(0.12, 0.45, 0.15));

	std::vector<std::shared_ptr<Material>> cubemap = { green, white, white, red, white, white };

	auto surroundingBox = std::make_shared<Box>(Point3(-1000, -1000, -1000), Point3(1000, 1000, 1000), cubemap);
	//auto lightSrc = std::make_shared<XZPlane>(-600, -400, -800, -700, -1, std::make_shared<DiffuseLight>(Color(6, 6, 6)));
	//auto lightSrc = std::make_shared<XZPlane>(-800, -400, -800, -500, -1, std::make_shared<DiffuseLight>(Color(7, 7, 7)));

	auto mirror = std::make_shared<Metal>(Color(1, 1, 1), 0.4);
	auto glass = std::make_shared<Dielectric>(1.56);

	std::shared_ptr<Hittable> bigBox = std::make_shared<Box>(Point3(-800, -999, -980), Vector3(280, 550, 280), mirror);
	rotateY(bigBox, 26);

	std::shared_ptr<Hittable> smallBox = std::make_shared<Box>(Point3(-470, -999, -850), Vector3(280, 280, 280), red);
	rotateY(smallBox, -23);

	world.add(surroundingBox);
	//world.add(lightSrc);

	world.add(bigBox);
	world.add(smallBox);

	return Scene{ camOptions, world };
}

#endif // !SCENES_H

#ifndef WORLDS_H

#define WORLDS_H

#include "../Hittables/Hittables.h"
#include "../Materials/Materials.h"
#include "../Textures/CheckerTexture.h"
#include "../Textures/ImageTexture.h"

//inline HittableList createWorld()
//{
//	Material* sunMaterial = new Diffuse(Color(0.9, 0.7, 0.4));
//
//	Texture* texture = new CheckerTexture();
//	//Material* materialGround = new Diffuse(texture);
//	//Material* materialGround = new Diffuse(Color(0.8, 0.8, 0.0));
//	Material* materialGround = new Diffuse(texture);
//	Material* materialCenter = new Diffuse(Color(0.1, 0.2, 0.5));
//	//Material* materialCenter = new Diffuse(Color(1.0, 0.2, 0.5));
//	//Material* materialLeft = new Dielectric(1.2);
//
//	Texture* texture2 = new ImageTexture("textures/earth.ppm");
//
//
//	Material* materialLeft = new Diffuse(texture2);
//	Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.0);
//	//Material* materialRight = new Metal(Color(0.8, 0.6, 0.2), 0.9);
//
//	HittableList objects;
//	//objects.add(new Sphere(Point3(0.0, 2, 2), 1.5, sunMaterial));
//	//objects.add(new Sphere(Point3(0.0, 2, -1), 0.5, sunMaterial));
//
//	//objects.add(new Sphere(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
//	//objects.add(new Sphere(Point3(0.0, -15.5, -1.0), 15.0, materialGround));
//
//	//objects.add(new XZPlane(-100, 100, -100, 100, -0.5, materialGround));
//
//	//objects.add(new Sphere(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
//	objects.add(std::make_shared<MovingSphere>(Point3(0.0, 0.0, -1.0), Point3(0.0, 0.3, -1.0), 0.5, 1.0, 0.2, materialCenter).get());
//	objects.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft).get());
//	//objects.add(new Sphere(Point3(-1.0, 0.0, -1.0), -0.45, materialLeft));
//	objects.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight).get());
//
//	return objects;
//}
//
//inline HittableList createWorld2()
//{
//	Texture* texture = new CheckerTexture();
//	Material* materialGround = new Diffuse(texture);
//
//	HittableList objects;
//
//	objects.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1, materialGround).get());
//
//	Texture* texture2 = new CheckerTexture();
//	//Material* materialGround = new Diffuse(texture);
//	//Material* materialGround = new Diffuse(Color(0.8, 0.8, 0.0));
//	Material* materialGround2 = new Diffuse(texture2);
//
//	objects.add(std::make_shared<Sphere>(Point3(0.0, -15.5, -1.0), 15.0, materialGround2).get());
//
//
//	Material* materialLight = new DiffuseLight(Color(1.0, 1.0, 1.0));
//	objects.add(std::make_shared<Sphere>(Point3(2.0, 0.5, 0.0), 0.5, materialLight).get());
//
//	return objects;
//}
//
//inline HittableList createWorld3()
//{
//	std::shared_ptr<Material> earth = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/earth.ppm"));
//	std::shared_ptr<Material> mars = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/mars.ppm"));
//	std::shared_ptr<Material> moon = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/moon.ppm"));
//
//	HittableList objects;
//
//	objects.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1, earth).get());
//	objects.add(std::make_shared<Sphere>(Point3(1.0, 1.2, -2.0), 0.7, mars).get());
//	objects.add(std::make_shared<Sphere>(Point3(-0.8, -0.9, -1.0), 0.6, moon).get());
//
//	return objects;
//}
//
//inline HittableList createWorld4()
//{
//	Material* earth = new Diffuse(new ImageTexture("textures/stofi.ppm"));
//	Material* mars = new Diffuse(new ImageTexture("textures/mars.ppm"));
//	Material* moon = new Diffuse(new ImageTexture("textures/moon.ppm"));
//
//	HittableList objects;
//
//	objects.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1, earth).get());
//	objects.add(std::make_shared<Sphere>(Point3(1.0, 1.3, -2.0), 0.7, mars).get());
//	objects.add(std::make_shared<Sphere>(Point3(-0.8, -0.9, -1.0), 0.6, moon).get());
//
//	return objects;
//}
//
//inline HittableList createWorld5()
//{
//	HittableList objects;
//
//	std::shared_ptr<Material> diffuse1 = std::make_shared<Diffuse>(Color(0.5, 0.5, 0));
//	objects.add(std::make_shared<Sphere>(Point3(0, 0, -5), 0.5, diffuse1).get());
//
//	auto diffuse = std::make_shared<Dielectric>(1.1);
//	objects.add(new XYPlane(0, 1, 0, 1, 0, diffuse));
//
//	auto texture = std::make_shared<Diffuse>(new CheckerTexture());
//	objects.add(new XZPlane(0, 1, 0, 2, 0, texture));
//
//	auto texture2 = std::make_shared<Diffuse>(Color(1,0,0));
//	objects.add(new YZPlane(0, 1, 0, 2, 1, texture2));
//
//	objects.add(new XYPlane(0, 1, 0, 1, 2, texture));
//
//	objects.add(new XZPlane(0, 1, 0, 2, 1, texture));
//
//	objects.add(new YZPlane(0, 1, 0, 2, 0, texture2));
//
//	return objects;
//}

#include "../Hittables/Translate.h"
#include "../Hittables/Rotate.h"

inline HittableList cornellBox()
{
	HittableList objects;

	auto red = std::make_shared<Diffuse>(Color(0.65, 0.05, 0.05));
	auto white = std::make_shared<Diffuse>(Color(0.73, 0.73, 0.73));
	auto green = std::make_shared<Diffuse>(Color(0.12, 0.45, 0.15));
	//auto light = new DiffuseLight(Color(3, 3, 0));
	auto light = std::make_shared<DiffuseLight>(Color(14, 14, 14));

	auto blue = new Diffuse(Color(0, 0, 1));

	objects.add(std::make_shared<YZPlane>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<YZPlane>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<XZPlane>(213, 343, 227, 332, 554, light));
	//objects.add(new XZPlane(113, 443, 127, 432, 554, light));
	objects.add(std::make_shared<XZPlane>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<XZPlane>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<XYPlane>(0, 555, 0, 555, 555, white));

	objects.add(std::make_shared<XYPlane>(0, 555, 0, 555, -801 , white));

	std::shared_ptr<Material> glass = std::make_shared<Dielectric>(1.60);
	//Material* glass = new Diffuse(Color(0.6,0.6,1));

	//Hittable* smallBox = new Box(Point3(-82.5, -82.5, -82.5), Point3(165.0, 165.0, 165.0), white);
	//smallBox = new RotateX(smallBox, 180);
	//smallBox = new Translate(smallBox, -Vector3(-82.5, -82.5, -82.5));
	//smallBox = new Translate(smallBox, Vector3(130.0, 0.0, 65.0));

	////smallBox = new Translate(smallBox, Vector3(130.0, 0.0, 65.0));

	//objects.add(smallBox);
	//objects.add(new Box(Point3(265.0, 0.0, 295.0), Point3(165.0, 330.0, 165.0), white));
	//objects.add(new Box(Point3(205.0, 0.0, 89.5), Point3(10, 500.0, 10), red));
	////objects.add(new Sphere(Point3(277.5, 540, 277.5), 30, glass));

	Vector3 diff;

	//Hittable* smallBox = new Box(Point3(110.0, 0.0, 65.0), Point3(165.0, 165.0, 165.0), white);
	std::shared_ptr<Hittable> smallBox = std::make_shared<Box>(Point3(110.0, 0.0, 65.0), Point3(165.0, 165.0, 165.0), white);

	rotateY(smallBox, 36);
	rotateX(smallBox, 16);
	rotateZ(smallBox, -29);

	objects.add(smallBox);

	std::shared_ptr<Hittable> bigBox = std::make_shared<Box>(Point3(285.0, 0.0, 295.0), Point3(165.0, 330.0, 165.0), white);
	//diff = bigBox->getOrigin() + bigBox->getCenter();

	//bigBox = new Translate(bigBox, -diff);
	//bigBox = new RotateY(bigBox, -15);
	//bigBox = new Translate(bigBox, diff);

	objects.add(bigBox);

	objects.add(std::make_shared<Sphere>(Point3(182.0, 245.0, 125.5), 80, glass));
	//objects.add(new Box(Point3(205.0, 0.0, 89.5), Point3(10, 500.0, 10), red));



	return objects;
}


//inline HittableList generateRandomWorld()
//{
//	HittableList world;
//	Material* groundMaterial = new Diffuse(Color(0.5, 0.5, 0.5));
//	world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial).get());
//
//	HittableList miniSpheres;
//	for (int i = -11; i < 11; ++i)
//	{
//		for (int j = -11; j < 11; ++j)
//		{
//			double randomNum = randomDouble();
//			Point3 center = Point3(i + 0.9 * randomDouble(), 0.2, j + 0.9 * randomDouble());
//
//			if ((center - Point3(4, 0.2, 0)).length() > 1)
//			{
//				if (randomNum < 0.5)
//				{
//					Color color = Color::random() * Color::random();
//					Material* material = new Diffuse(color);
//					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material).get());
//				}
//				else if (randomNum < 0.8)
//				{
//					Color color = Color::random() * Color::random();
//					Material* material = new Metal(color, randomDouble());
//					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material).get());
//				}
//				else
//				{
//					Material* material = new Dielectric(1 + randomDouble() * 0.6);
//					miniSpheres.add(std::make_shared<Sphere>(center, 0.2, material).get());
//				}
//			}
//		}
//	}
//
//	world.add(new BVH(miniSpheres, 0, 0));
//
//	Material* dielectric = new Dielectric(1.5);
//	Material* diffuse = new Diffuse(Color(0.53, 0.81, 0.94));
//	Material* metal = new Metal(Color(0.7, 0.6, 0.5), 0.0);
//
//	world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, dielectric).get());
//	world.add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, diffuse).get());
//	world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, metal).get());
//
//	return world;
//}

#endif // !WORLDS_H


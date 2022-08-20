#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Utility.h"

void createImage(std::ofstream& output, int width, int height);
Color rayColor(const Ray& ray, const HittableList& world);
double sphereHit(const Vector3& center, double radius, const Ray& ray);

int main()
{
	// Image

	const double aspectRatio = 16.0 / 9.0;
	const int width = 1080;
	const int height = static_cast<int>(width / aspectRatio);

	std::ofstream stream("image.ppm");
	createImage(stream, width, height);
	stream.close();
};

void createImage(std::ofstream& output, int width, int height)
{
	// Camera
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * ((double)width / (double)height);
	double focalLength = 1.0;

	Point3 origin = Point3(0, 0, 0);
	Vector3 horizontalPlane = Vector3(viewportWidth, 0, 0);
	Vector3 verticalPlane = Vector3(0, viewportHeight, 0);
	Point3 upperLeftCorner = origin - horizontalPlane / 2 + verticalPlane / 2 - Vector3(0, 0, focalLength);

	HittableList objects;
	objects.add(new Sphere(Point3(0, -100.5, -1), 100));
	objects.add(new Sphere(Point3(0, 0, -1), 0.5));

	output << "P3" << std::endl;
	output << width << " " << height << std::endl;
	output << "255" << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double u = (double)i / (height - 1);
			double v = (double)j / (width - 1);

			Ray ray = Ray(origin, upperLeftCorner - u * verticalPlane + v * horizontalPlane - origin);

			Color pixel = rayColor(ray, objects);
			writeColor(output, pixel);
		}

		int percentage = ((double)i / (height - 1)) * 100;
		std::cout << "\rPercantage: " << percentage << std::flush;
	}

	std::cout << "\nDone!" << std::endl;
}

Color rayColor(const Ray& ray, const HittableList& world) 
{
	HitRecord record;
	
	if (world.isHit(ray, 0, INF, record))
		return 0.5 * (record.normalVector + Color(1, 1, 1));

	Vector3 unitDirecion = unitVector(ray.direction());
	double t = 0.5 * (unitDirecion.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0);
}

double sphereHit(const Vector3& center, double radius, const Ray& ray)
{
	Vector3 diff = ray.origin() - center;
	double a = ray.direction().lengthSquared();
	double halfB = dotProduct(ray.direction(), diff);
	double c = diff.lengthSquared() - radius * radius;
	double discriminant = halfB * halfB - a * c;

	if (discriminant < 0)
		return -1.0;
	else
		return (-halfB - sqrt(discriminant)) / a;
}


//Color ray_color(const Ray& r) {
//    Vector3 unit_direction = unitVector(r.direction());
//    auto t = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
//}
//
//int main() {
//
//    // Image
//    const auto aspect_ratio = 16.0 / 9.0;
//    const int image_width = 400;
//    const int image_height = static_cast<int>(image_width / aspect_ratio);
//
//    // Camera
//
//    auto viewport_height = 2.0;
//    auto viewport_width = aspect_ratio * viewport_height;
//    auto focal_length = 1.0;
//
//    auto origin = Point3(0, 0, 0);
//    auto horizontal = Vector3(viewport_width, 0, 0);
//    auto vertical = Vector3(0, viewport_height, 0);
//    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);
//
//    // Render
//    
//    std::ofstream stream("image2.ppm");
//
//    stream << "P3\n" << image_width << " " << image_height << "\n255\n";
//
//    for (int j = image_height - 1; j >= 0; --j) {
//        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//        for (int i = 0; i < image_width; ++i) {
//            auto u = double(i) / (image_width - 1);
//            auto v = double(j) / (image_height - 1);
//            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
//            Color pixel_color = ray_color(r);
//            writeColor(stream, pixel_color);
//        }
//    }
//
//    std::cerr << "\nDone.\n";
//}
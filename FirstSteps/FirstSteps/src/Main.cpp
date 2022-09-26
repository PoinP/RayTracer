#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>

#include "Core/Core.h"
#include "Hittables/HittableList.h"
#include "Utility/Timer.h"
#include "Utility/Worlds.h"
#include "Utility/Utility.h"
#include "Multi-Threading/Worker.h"

#define ASYNC

// TODO: FIX ALL OF THE MEMORY LEAKS hihi ^^

struct Workspace;

void createImage(std::ofstream& output, const Workspace& workSpace);
void createImageHT(std::ofstream& output, const Workspace& workSpace);

void writeToOutput(std::ostream& output, Color** colors, unsigned width, unsigned height);

struct Workspace
{
	unsigned width;
	unsigned height;
	unsigned sampleCount;
	unsigned maxDepth;
	CameraOptions camOptions;
	HittableList world;
};

Workspace getWorkspace()
{
	//const double aspectRatio = 16.0 / 9.0;
	const double aspectRatio = 1.0;
	const unsigned width = 1900;
	const unsigned height = static_cast<unsigned>(width / aspectRatio);
	const unsigned int sampleCount = 1600;
	const unsigned int maxDepth = 50;

	//CameraOptions camOptions = {
	//	Point3(0.0, 0.0, 0.0),
	//	Point3(13.0, 2.0, 3.0),
	//	Point3(0.0, 1.0, 0.0),
	//	aspectRatio,
	//	20,
	//	0.1,
	//	10
	//};
	
	//CameraOptions camOptions = {
	//	Point3(0.0, 0.0, -1.0),
	//	Point3(0.0, 1.5, 5.0),
	//	Point3(0.0, 1.0, 0.0),
	//	aspectRatio,
	//	20,
	//	0,
	//	(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	//};

	//CameraOptions camOptions = {
	//Point3(0.0, 0.0, -1.0),
	//Point3(0.0, 1.5, 10.0),
	//Point3(0.0, 1.0, 0.0),
	//aspectRatio,
	//20,
	//0,
	//(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	//};

	//CameraOptions camOptions = {
	//Point3(278.0, 278.0, 0),
	//Point3(278, 278, -500),
	//Point3(0.0, 1.0, 0.0),
	//aspectRatio,
	//40,
	//0,
	//(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	//};

	CameraOptions camOptions = {
	Point3(0.0, 0.0, 0.0),
	Point3(0, 70, -195),
	Point3(0.0, 1.0, 0.0),
	aspectRatio,
	40,
	0,
	(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	};

	//CameraOptions camOptions = {
	//Point3(-450.0, 200.0, 1000.0),
	//Point3(-550, 300, 600),
	//Point3(0.0, 1.0, 0.0),
	//aspectRatio,
	//25,
	//0,
	//(Point3(0.0, 0.0, -1.0) - Point3(0.0, 1.5, 5.0)).length()
	//};

	//HittableList world = createWorld();
	//HittableList world = cornellBox();
	HittableList world = skyboxTest();

	return Workspace{
		width,
		height,
		sampleCount,
		maxDepth,
		camOptions,
		world
	};
}

int main()
{
	Timer t;

	Workspace ws = getWorkspace();

#ifdef ASYNC
	std::ofstream stream("testing\\skybox_test.ppm");
	createImageHT(stream, ws);
#else
	std::ofstream stream("testing\\rotations.ppm");
	createImage(stream, ws);
#endif // ASYNC

	stream.close();
};


void createImageHT(std::ofstream& output, const Workspace& ws)
{
	Camera cam(ws.camOptions);

	Color** colors = new Color * [ws.height];
	for (int i = 0; i < (int)ws.height; i++)
		colors[i] = new Color[ws.width];

	int availableThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(availableThreads);

	Worker::setupWorkforce(ws.width, ws.height, 32);

	for (std::thread& thread : threads)
		thread = std::thread(Worker{}, cam, ws.world, ws.sampleCount, ws.maxDepth, colors);

	for (std::thread& thread : threads)
	{
		thread.join();
		std::cout << "\rPercantage: " << 100 << std::flush;
	}

	writeToOutput(output, colors, ws.width, ws.height);

	for (size_t i = 0; i < ws.height; i++)
		delete[] colors[i];

	delete[] colors;
}


void createImage(std::ofstream& output, const Workspace& ws)
{
	Camera cam(ws.camOptions);

	Color** colors = new Color * [ws.height];
	for (size_t i = 0; i < ws.height; i++)
		colors[i] = new Color[ws.width];

	HittableList world = ws.world;

	for (size_t i = 0; i < ws.height; ++i)
	{
		for (size_t j = 0; j < ws.width; ++j)
		{
			Color pixel;

			for (size_t s = 0; s < ws.sampleCount; ++s)
			{
				double u = (j + randomDouble()) / ((double)ws.width - 1);
				double v = (i + randomDouble()) / ((double)ws.height - 1);

				Ray ray = cam.getRay(u, v);

				pixel += rayColor(ray, world, ws.maxDepth);
			}

			colors[i][j] = getColor(pixel, ws.sampleCount);
		}

		int percentage = (int)((i / ((double)ws.height - 1)) * 100);
		std::cout << "\rPercantage: " << percentage << std::flush;
	}

	writeToOutput(output, colors, ws.width, ws.height);

	std::cout << "\nDone!" << std::endl;
}

void writeToOutput(std::ostream& output, Color** colors, unsigned width, unsigned height)
{
	std::cout << "\nWriting to file:" << std::endl;
	output << "P3" << std::endl;
	output << width << " " << height << std::endl;
	output << "255" << std::endl;

	std::string fileContent;
	fileContent.reserve(2048);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			fileContent += std::to_string((int)colors[i][j].x()) + " " +
				std::to_string((int)colors[i][j].y()) + " " +
				std::to_string((int)colors[i][j].z()) + "\n";

			if (fileContent.size() >= 2048 || (i + 1 >= height && j + 1 >= width))
			{
				output << fileContent;
				fileContent.clear();
				fileContent.reserve(2048);
			}
		}

		int percentage = (int)((i / ((double)height - 1)) * 100);
		std::cout << "\rPercantage: " << percentage << std::flush;
	}
}
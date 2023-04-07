#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>

#include "Core/Core.h"
#include "Hittables/HittableList.h"
#include "Utility/Timer.h"
#include "Utility/Scenes.h"
#include "Utility/Utility.h"
#include "Multi-Threading/Worker.h"
#include "Multi-Threading/WorkerWindow.h"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define ASYNC
#define WINDOW_ASYNC
#define WINDOW

// TODO: FIX ALL OF THE MEMORY LEAKS hihi ^^

struct Workspace;

void createImage(std::ofstream& output, const Workspace& workSpace);
void createImageOnWindow(sf::RenderWindow& window, const Workspace& workSpace);
void createImageHT(std::ofstream& output, const Workspace& workSpace);
void createImageHTOnWindow(sf::RenderWindow& window, const Workspace& workSpace);

void writeToOutput(std::ostream& output, Color** colors, unsigned width, unsigned height);

struct Workspace
{
	unsigned width;
	unsigned height;
	unsigned sampleCount;
	unsigned maxDepth;
	Scene scene;
};

Workspace getWorkspace()
{
	const double aspectRatio = 1.0;
	const unsigned width = 600;
	const unsigned height = static_cast<unsigned>(width / aspectRatio);
	const unsigned int sampleCount = 50;
	const unsigned int maxDepth = 50;

	return Workspace{
		width,
		height,
		sampleCount,
		maxDepth,
		cornellBoxScene(aspectRatio)
	};
}

int main()
{
	sf::RenderWindow window;
	Timer t;
	Workspace ws;

	try
	{
		ws = getWorkspace();
		window.create(sf::VideoMode(ws.width, ws.height), "test");
	}
	catch (const std::exception& ex)
	{
		std::cout << "An error has occured: " << ex.what() << "\n";
		std::cout << "Exitting...\n";

		return -1;
	}

#ifdef WINDOW_ASYNC
	createImageHTOnWindow(window, ws);
#endif
	
#ifdef WINDOW
	createImageOnWindow(window, ws);
#endif
	
#ifdef ASYNC 
	std::ofstream stream("testing\\image.ppm");
	createImageHT(stream, ws);
	stream.close();
#else
	std::ofstream stream("testing\\image.ppm");
	createImageOnWindow(window, ws);
	stream.close();
#endif

};



std::mutex mutex;
void display(sf::RenderWindow& window, sf::Image& image)
{
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);
	mutex.lock();
	window.setActive(true);
	window.clear();
	window.draw(sprite);
	window.display();
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	window.setActive(false);
	mutex.unlock();
}

void createImageHT(std::ofstream& output, const Workspace& ws)
{
	Camera cam(ws.scene.cameraOptions);

	Color** colors = new Color * [ws.height];
	for (int i = 0; i < (int)ws.height; i++)
		colors[i] = new Color[ws.width];

	int availableThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(availableThreads);
	
	Worker::setupWorkforce(ws.width, ws.height, 32);

	for (std::thread& thread : threads)
		thread = std::thread(Worker{}, cam, ws.scene.world, ws.sampleCount, ws.maxDepth, colors);

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

void createImageHTOnWindow(sf::RenderWindow& window, const Workspace& ws)
{
	Camera cam(ws.scene.cameraOptions);

	Color** colors = new Color * [ws.height];
	for (int i = 0; i < (int)ws.height; i++)
		colors[i] = new Color[ws.width];

	int availableThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(availableThreads);
	
	WorkerWindow::setupWorkforce(ws.width, ws.height, 32);

	std::mutex mutexDisplaying;
	
	sf::Image image;
	image.create(ws.width, ws.height);
	window.setActive(false);
	for (std::thread& thread : threads)
		thread = std::thread([&]() {
			WorkerWindow worker(cam, ws.scene.world, ws.sampleCount, ws.maxDepth, colors, image, window, mutexDisplaying);
		});
	
	for (std::thread& thread : threads)
	{
		thread.join();
		std::cout << "\rPercantage: " << 100 << std::flush;
	}
	window.setActive(true);
	while (window.isOpen())
	{
		display(window, image);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	for (size_t i = 0; i < ws.height; i++)
		delete[] colors[i];

	delete[] colors;
}

void createImageOnWindow(sf::RenderWindow& window, const Workspace& ws)
{
	Camera cam(ws.scene.cameraOptions);
	sf::Image img;
	img.create(ws.width, ws.height);
	
	Color** colors = new Color * [ws.height];
	for (size_t i = 0; i < ws.height; i++)
		colors[i] = new Color[ws.width];

	HittableList world = ws.scene.world;

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
			img.setPixel(j, i, sf::Color(colors[i][j].x(), colors[i][j].y(), colors[i][j].z()));
			display(window, img);
		}

		int percentage = (int)((i / ((double)ws.height - 1)) * 100);
		std::cout << "\rPercantage: " << percentage << std::flush;
	}
	sf::Texture checkTexture;
	checkTexture.create(ws.width, ws.height);
	checkTexture.update(img);
	sf::Sprite sprite(checkTexture);
	img.saveToFile("pp.png");
	while (window.isOpen())
	{
		//display(window, img);
		window.clear();
		window.draw(sprite);
		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	std::cout << "\nDone!" << std::endl;
}

void createImage(std::ofstream& output, const Workspace& ws)
{
	Camera cam(ws.scene.cameraOptions);

	Color** colors = new Color * [ws.height];
	for (size_t i = 0; i < ws.height; i++)
		colors[i] = new Color[ws.width];

	HittableList world = ws.scene.world;

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
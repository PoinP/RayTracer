#include "WorkerWindow.h"

#include "../Utility/Utility.h"
#include "../Core/Color.h"
#include "../Core/RayColor.h"

#include <mutex>
#include <stdexcept>

#include <SFML/Graphics.hpp>

//Does not work with sky boxes!!
//#define LEGACY_RENDER

int WorkerWindow::m_LastId = 0;
unsigned WorkerWindow::m_BlockSize = 0;
unsigned WorkerWindow::m_Width = 0;
unsigned WorkerWindow::m_Height = 0;
unsigned WorkerWindow::m_WCap = 0;
unsigned WorkerWindow::m_HCap = 0;
bool** WorkerWindow::m_Tasks = nullptr;

static void draw(sf::Image& image, int x, int y, sf::Color color)
{
	image.setPixel(x, y, color);
}

static void display(sf::RenderWindow& window, sf::Image& image, std::mutex& mutex)
{
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);
	
	mutex.lock();
	window.setActive(false);
	window.clear();
	window.draw(sprite);
	window.display();
	sf::Event event;
	while (window.pollEvent(event))
	{
	}
	window.setActive(false);
	mutex.unlock();
}

WorkerWindow::WorkerWindow(const Camera& cam, const HittableList& world, unsigned sampleCount, unsigned maxDepth, Color** colors, sf::Image& image, sf::RenderWindow& window, std::mutex& mutex)
    :m_Id(m_LastId++)
{
	bool isDone = false;

	if (!m_Tasks)
		throw std::invalid_argument("Workforce not set! Please set workforce!");

	do
	{
		if (m_Id == 0)
		{
			int percentage = (int)((tasksDoneWin / ((double)m_HCap)) * 100);
			std::cout << "\rPercantage: " << percentage << std::flush;
		}

		if (!getNextTask())
		{
			isDone = true;
			continue;
		}

		for (int i = (int)m_CoordY; i < (int)m_CoordY + (int)m_BlockSize; ++i)
		{
			for (int j = m_CoordX; j < (int)m_CoordX + (int)m_BlockSize; ++j)
			{
				if (i < 0 || i >= (int)m_Height || j < 0 || j >= (int)m_Width)
					continue;

				Color pixel;

				for (size_t s = 0; s < sampleCount; ++s)
				{
					double u = (j + randomDouble()) / ((double)m_Width - 1);
					double v = (i + randomDouble()) / ((double)m_Height - 1);

					Ray ray = cam.getRay(u, v);

#ifdef LEGACY_RENDER
					pixel += rayColor(ray, world, maxDepth);
#else
					pixel += rayColor(ray, Color(0, 0, 0), world, maxDepth);
#endif // LEGACY_RENDER
				}

				colors[i][j] = getColor(pixel, sampleCount);
				draw(image, j, i, sf::Color(colors[i][j].x(), colors[i][j].y(), colors[i][j].z()));
			}
			if (i % 10 == 0)
				display(window, image, mutex);
		}
	} while (!isDone);

	m_LastId--;

}

WorkerWindow::~WorkerWindow()
{
	if (m_LastId == 0)
	{
		for (int i = 0; i < (int)m_HCap; i++)
		{
			delete[] m_Tasks[i];
		}

		delete[] m_Tasks;
	}
}


void WorkerWindow::setupWorkforce(unsigned width, unsigned height, unsigned blockSize)
{
	m_BlockSize = blockSize;
	m_Width = width;
	m_Height = height;
	m_WCap = (m_Width + m_BlockSize - 1) / m_BlockSize;
	m_HCap = (m_Height + m_BlockSize - 1) / m_BlockSize;

	m_Tasks = new bool* [m_HCap];
	for (size_t i = 0; i < m_HCap; i++)
		m_Tasks[i] = new bool[m_WCap]();
}

bool WorkerWindow::getNextTask()
{
	static std::mutex m;

	std::lock_guard<std::mutex> lock(m);

	int x, y;

	bool isFound = false;

	while (!isFound)
	{
		moveInPattern(x, y);
		if (x < 0 || x >= (int)m_WCap || y < 0 || y >= (int)m_HCap)
			break;

		if (!m_Tasks[y][x])
		{
			isFound = true;
			m_CoordX = x * m_BlockSize;
			m_CoordY = y * m_BlockSize;
			m_Tasks[y][x] = true;
		}
	}

	return isFound;
}

void WorkerWindow::moveInPattern(int& varX, int& varY) const
{
	static int x = -1;
	static int y = 0;

	if (x + 1 >= (int)m_WCap)
	{
		x = 0;
		y++;
		tasksDoneWin++;
	}
	else
		x++;

	varX = x;
	varY = y;
}
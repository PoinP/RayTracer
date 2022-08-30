#include "Worker.h"

#include "Utility.h"
#include "Color.h"
#include "RayColor.h"

#include <mutex>
#include <stdexcept>

int Worker::m_LastId = 0;
unsigned Worker::m_BlockSize = 0;
unsigned Worker::m_Width = 0;
unsigned Worker::m_Height = 0;
unsigned Worker::m_WCap = 0;
unsigned Worker::m_HCap = 0;
bool** Worker::m_Tasks = nullptr;


Worker::Worker()
    :m_Id(m_LastId++)
{
}

Worker::~Worker()
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

void Worker::operator()(const Camera& cam, const HittableList& world, unsigned sampleCount, unsigned maxDepth, Color** colors)
{
	bool isDone = false;

	if (!m_Tasks)
		throw std::invalid_argument("Workforce not set! Please set workforce!");

	do
	{
		if (m_Id == 0)
		{
			int percentage = (int)((tasksDone / ((double)m_HCap)) * 100);
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

					pixel += rayColor(ray, world, sampleCount);
				}

				colors[i][j] = getColor(pixel, sampleCount);
			}
		}
	} while (!isDone);

	m_LastId--;
}

void Worker::setupWorkforce(unsigned width, unsigned height, unsigned blockSize)
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

bool Worker::getNextTask()
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

void Worker::moveInPattern(int& varX, int& varY) const
{
	static int x = -1;
	static int y = 0;

	if (x + 1 >= (int)m_WCap)
	{
		x = 0;
		y++;
		tasksDone++;
	}
	else
		x++;

	varX = x;
	varY = y;
}
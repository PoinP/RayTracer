#ifndef WORKERWIN_H

#define WORKERWIN_H

#include <atomic>

#include "../Core/Ray.h"
#include "../Core/Camera.h"
#include "../Hittables/HittableList.h"

static std::atomic<int> tasksDoneWin = 0;

#include <mutex>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

void draw(sf::Image& image, int x, int y, sf::Color color);
void display(sf::RenderWindow& window, sf::Image& image, std::mutex& mutex);

class WorkerWindow
{
public:
	WorkerWindow(const Camera& cam, const HittableList& world, unsigned sampleCount, unsigned maxDepth, Color** colors, sf::Image& image, sf::RenderWindow& window, std::mutex& mutex);
	~WorkerWindow();

	bool getNextTask();
	void moveInPattern(int& varX, int& varY) const;

	static void setupWorkforce(unsigned width, unsigned height, unsigned blockSize);

private:
	unsigned m_CoordX{};
	unsigned m_CoordY{};
	unsigned m_Id;

	static unsigned m_BlockSize;
	static unsigned m_Width;
	static unsigned m_Height;
	static unsigned m_WCap;
	static unsigned m_HCap;

	static bool** m_Tasks;

	static int m_LastId;

private:
	WorkerWindow& operator=(const WorkerWindow& other) = delete;
};

#endif // !WORKER_H
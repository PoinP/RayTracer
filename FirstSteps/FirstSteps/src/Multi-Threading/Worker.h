#ifndef WORKER_H

#define WORKER_H

#include <atomic>

#include "../Core/Ray.h"
#include "../Core/Camera.h"
#include "../Hittables/HittableList.h"

static std::atomic<int> tasksDone = 0;

class Worker
{
public:
	Worker();
	~Worker();

	void operator()(const Camera& cam, const HittableList& world, unsigned sampleCount, unsigned maxDepth, Color** colors);
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
	Worker& operator=(const Worker& other) = delete;
};

#endif // !WORKER_H
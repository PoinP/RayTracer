#ifndef UTILITY_H

#define UTILITY_H

#include <limits>

// Constants

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double degreesToRadians(double degrees)
{
	return degrees * PI / 180.0;
}

#endif // !UTILITY_H

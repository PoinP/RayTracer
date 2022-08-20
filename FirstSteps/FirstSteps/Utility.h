#ifndef UTILITY_H

#define UTILITY_H

#include <limits>
#include <stdlib.h>

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}

inline double randomDouble()
{
    return (double)rand() / ((double)RAND_MAX + 1);
}

inline double randomDouble(double min, double max)
{
    return randomDouble() * (max - min) + min;
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline Point3 randomPointInUnitSphere()
{
    while (true)
    {
        Point3 point = Vector3::random(-1, 1);
        if (point.lengthSquared() >= 1) continue;
        return point;
    }
}

inline Vector3 randomUnitVector()
{
    return unitVector(randomPointInUnitSphere());
}

#endif // !UTILITY_H

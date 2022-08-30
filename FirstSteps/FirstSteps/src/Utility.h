#ifndef UTILITY_H

#define UTILITY_H

#include <limits>
#include <stdlib.h>
#include <random>

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}

inline std::mt19937 getPersonalRNG() {
    std::random_device r;
    std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
    return std::mt19937(seed);
}

inline double randomDouble()
{
    static thread_local std::mt19937 generator = getPersonalRNG();
    std::uniform_real_distribution<double> distribution(0, 1);
    return distribution(generator);
}

inline double randomDouble(double min, double max)
{
    return randomDouble() * (max - min) + min;
}

inline double randomDoubleThreadSafe(double min, double max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline Vector3 randomInUnitSphere()
{
    while (true)
    {
        Vector3 vec = Vector3::random(-1, 1);
        if (vec.lengthSquared() >= 1) continue;
        return vec;
    }
}

inline Vector3 randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

inline Vector3 randomInUnitDisk()
{
    while (true)
    {
        Vector3 vec = Vector3(randomDouble(), randomDouble(), 0);
        if (vec.lengthSquared() > 1) continue;
        return vec;
    }
}

#endif // !UTILITY_H

#ifndef UTILITY_H

#define UTILITY_H

#include <limits>
#include <random>
#include <mutex>
#include <array>

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}

inline std::mt19937_64 getPersonalRNG() 
{
    std::random_device rd;
    
    auto randVals = std::array<std::mt19937_64::result_type, std::mt19937_64::state_size>{};

    for (auto& val : randVals)
        val = (static_cast<uint64_t>(rd()) << 32) | static_cast<uint64_t>(rd());

    std::seed_seq seed(randVals.begin(), randVals.end());
    return std::mt19937_64(seed);
}

inline double randomDouble()
{
    static thread_local std::mt19937_64 generator = getPersonalRNG();
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double randomDouble(double min, double max)
{
    return randomDouble() * (max - min) + min;
}

inline int randomInt(int min, int max)
{
    return static_cast<int>(randomDouble(min, max + 1.0));
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

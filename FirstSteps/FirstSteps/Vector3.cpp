#include "Vector3.h"

#include <math.h>
#include "Utility.h"

Vector3::Vector3()
    : m_Coords { 0, 0, 0 }
{}

Vector3::Vector3(double x, double y, double z)
    : m_Coords { x, y, z }
{
}

Vector3::Vector3(const Vector3& other)
    : m_Coords { other.m_Coords[0], other.m_Coords[1], other.m_Coords[2] }
{
}

Vector3& Vector3::operator=(const Vector3& other)
{
    if (this != &other) 
    {
        m_Coords[0] = other.m_Coords[0];
        m_Coords[1] = other.m_Coords[1];
        m_Coords[2] = other.m_Coords[2];
    }

    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-m_Coords[0], -m_Coords[1], -m_Coords[2]);
}

double Vector3::operator[](int index) const
{
    return m_Coords[index];
}

double& Vector3::operator[](int index)
{
    return m_Coords[index];
}

Vector3& Vector3::operator+=(const Vector3& otherVec)
{
    m_Coords[0] += otherVec.m_Coords[0];
    m_Coords[1] += otherVec.m_Coords[1];
    m_Coords[2] += otherVec.m_Coords[2];

    return *this;
}

Vector3& Vector3::operator*=(double scalar)
{
    m_Coords[0] *= scalar;
    m_Coords[1] *= scalar;
    m_Coords[2] *= scalar;

    return *this;
}

Vector3& Vector3::operator/=(double scalar)
{
    *this *= 1 / scalar;
    return *this;
}

double Vector3::x() const
{
    return m_Coords[0];
}

double Vector3::y() const
{
    return m_Coords[1];
}

double Vector3::z() const
{
    return m_Coords[2];
}

double Vector3::length() const
{
    return sqrt(lengthSquared());
}

double Vector3::lengthSquared() const
{
    return m_Coords[0] * m_Coords[0] + m_Coords[1] * m_Coords[1] + m_Coords[2] * m_Coords[2];
}

Vector3 Vector3::random()
{
    return Vector3(randomDouble(), randomDouble(), randomDouble());
}

Vector3 Vector3::random(int min, int max)
{
    return Vector3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

void operator<<(std::ostream& stream, const Vector3& vector)
{
    stream << vector.x() << " " << vector.y() << " " << vector.z();
}

Vector3 operator+(const Vector3& vector1, const Vector3& vector2)
{
    return Vector3(vector1.x() + vector2.x(), vector1.y() + vector2.y(), vector1.z() + vector2.z());
}

Vector3 operator-(const Vector3& vector1, const Vector3& vector2)
{
    return Vector3(vector1.x() - vector2.x(), vector1.y() - vector2.y(), vector1.z() - vector2.z());
}

Vector3 operator*(const Vector3& vector, double scalar)
{
    return Vector3(vector.x() * scalar, vector.y() * scalar, vector.z() * scalar);
}

Vector3 operator*(double scalar, const Vector3& vector)
{
    return vector * scalar;
}

Vector3 operator/(const Vector3& vector, double scalar)
{
    return vector * (1 / scalar);
}

Vector3 operator/(double scalar, const Vector3& vector)
{
    return vector / scalar;
}

double dotProduct(const Vector3& vector1, const Vector3& vector2)
{
    return vector1.x() * vector2.x() + vector1.y() * vector2.y() + vector1.z() * vector2.z();
}

Vector3 crossProduct(const Vector3& vector1, const Vector3& vector2)
{
    return Vector3(vector1.y() * vector2.z() - vector1.z() * vector2.y(), 
                   vector1.z() * vector2.x() - vector1.x() * vector2.z(),
                   vector1.x() * vector2.y() - vector1.y() * vector2.x());
}

Vector3 unitVector(const Vector3& vector)
{
    return vector / vector.length();
}

#ifndef COLOR_H

#define COLOR_H

#include "Vector3.h"
#include "Utility.h"

inline void writeColor(std::ostream& stream, Color pixelColor, unsigned int sampleCount)
{
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();

	double scale = 1.0 / sampleCount;

	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

	stream << (int)(255.999 * clamp(r, 0, 1.0)) << " "
		<< (int)(255.999 * clamp(g, 0, 1.0)) << " "
		<< (int)(255.999 * clamp(b, 0, 1.0)) << std::endl;
}

inline Color getColor(Color pixelColor, unsigned int sampleCount)
{
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();

	double scale = 1.0 / sampleCount;

	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

	return Color((int)(255.999 * clamp(r, 0, 1.0)), (int)(255.999 * clamp(g, 0, 1.0)), (int)(255.999 * clamp(b, 0, 1.0)));
}

#endif // !COLOR_H
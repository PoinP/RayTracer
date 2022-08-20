#ifndef COLOR_H

#define COLOR_H

#include "Vector3.h"

void writeColor(std::ostream& stream, Color pixelColor)
{
	stream << (int)(255.999 * pixelColor.x()) << " "
		<< (int)(255.999 * pixelColor.y()) << " "
		<< (int)(255.999 * pixelColor.z()) << std::endl;
}

#endif // !COLOR_H
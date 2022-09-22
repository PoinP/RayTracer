#ifndef TEXTURE_H

#define TEXTURE_H

#include "../Core/Color.h"
#include "../Core/Vector3.h"

class Texture
{
public:
	virtual Color value(double u, double v, const Point3& p) const = 0;
	virtual ~Texture() {}
};

#endif // !TEXTURE_H

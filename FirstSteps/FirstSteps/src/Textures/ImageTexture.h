#ifndef IMAGE_TEXTURE_H

#define IMAGE_TEXTURE_H

#include "Texture.h"
#include "../Core/Color.h"

#include <fstream>

class ImageTexture : public Texture
{
public:
	ImageTexture(const char* imagePath);
	ImageTexture(const Color** data, unsigned width, unsigned height);
	~ImageTexture();

	virtual Color value(double u, double v, const Point3& p) const override;

private:
	unsigned m_Width, m_Height;
	Color** m_Data;

	void readColors(std::ifstream& fileStream, double maxColor = 256.0);

private:
	ImageTexture(const ImageTexture&) = delete;
	ImageTexture& operator=(const ImageTexture&) = delete;
};


#endif // !IMAGE_TEXTURE_H
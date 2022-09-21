#include "ImageTexture.h"

#include <fstream>
#include <stdexcept>
#include <string>

ImageTexture::ImageTexture(const char* imagePath)
{
    std::ifstream inputStream(imagePath, std::ios::in | std::ios::app);

    if (!inputStream || !inputStream.is_open())
        throw std::invalid_argument("Error loading an image texture!");

    char format[3];
    inputStream >> format;

    if (strncmp(format, "P3", 2) && strncmp(format, "p3", 2))
        throw std::invalid_argument("Invalid file format!");

    inputStream >> m_Width >> m_Height;

    int maxColor;

    inputStream >> maxColor;

    readColors(inputStream, maxColor);

    inputStream.close();
}

ImageTexture::ImageTexture(const Color** data, unsigned width, unsigned height)
    : m_Width(width), m_Height(height), m_Data(new Color* [m_Height])
{
    for (int i = 0; i < m_Height; ++i)
    {
        m_Data[i] = new Color [m_Width];

        for (int j = 0; j < m_Width; ++j)
        {
            m_Data[i][j] = data[i][j];
        }
    }
}

ImageTexture::~ImageTexture()
{
    for (int i = 0; i < m_Height; i++)
    {
        delete[] m_Data[i];
    }

    delete[] m_Data;
}

Color ImageTexture::value(double u, double v, const Point3& p) const
{
    int width = floor(u * m_Width);
    int height = floor(v * m_Height);

    return m_Data[height][width];
}

void ImageTexture::readColors(std::ifstream& fileStream, double maxColor)
{
    int r, g, b;
    maxColor -= 0.0001;

    m_Data = new Color * [m_Height];

    for (int i = 0; i < m_Height; ++i)
    {
        m_Data[i] = new Color[m_Width];

        for (int j = 0; j < m_Width; ++j)
        {
            fileStream >> r >> g >> b;

            m_Data[i][j] = Color(r / maxColor, g / maxColor, b / maxColor);
        }
    }
}

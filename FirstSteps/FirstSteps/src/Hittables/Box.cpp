#include "Box.h"

Box::Box(const Point3& origin, const Point3& dimensions, std::shared_ptr<Material> material)
	: m_Origin(origin), m_Dimension(dimensions)
{
	double x, y, z;
	double w, h, l;

	x = origin.x();
	y = origin.y();
	z = origin.z();

	w = dimensions.x();
	h = dimensions.y();
	l = dimensions.z();

	m_Planes.add(std::make_shared<YZPlane>(y, y + h, z, z + l, x, material));
	m_Planes.add(std::make_shared<YZPlane>(y, y + h, z, z + l , x + w, material));
	m_Planes.add(std::make_shared<XZPlane>(x, x + w, z, z + l, y, material));
	m_Planes.add(std::make_shared<XZPlane>(x, x + w, z, z + l, y + h, material));
	m_Planes.add(std::make_shared<XYPlane>(x, x + w, y, y + h, z, material));
	m_Planes.add(std::make_shared<XYPlane>(x, x + w, y, y + h, z + l, material));
}

#include "../Materials/Materials.h";
#include "../Textures/Textures.h";

Box::Box(const Point3& origin, const Point3& dimensions, const std::vector<std::shared_ptr<Material>>& cubeMap)
	: m_Origin(origin), m_Dimension(dimensions)
{
	double x, y, z;
	double w, h, l;

	x = origin.x();
	y = origin.y();
	z = origin.z();

	w = dimensions.x();
	h = dimensions.y();
	l = dimensions.z();

	auto test = std::make_shared<Diffuse>(std::make_shared<ImageTexture>("textures/earth.ppm"));

	m_Planes.add(std::make_shared<YZPlane>(y, y + h, z, z + l, x, cubeMap[3]));
	m_Planes.add(std::make_shared<YZPlane>(y, y + h, z, z + l, x + w, cubeMap[0]));
	m_Planes.add(std::make_shared<XZPlane>(x, x + w, z, z + l, y, cubeMap[1]));
	m_Planes.add(std::make_shared<XZPlane>(x, x + w, z, z + l, y + h, cubeMap[4]));
	m_Planes.add(std::make_shared<XYPlane>(x, x + w, y, y + h, z, cubeMap[2]));
	m_Planes.add(std::make_shared<XYPlane>(x, x + w, y, y + h, z + l, cubeMap[5]));
}

bool Box::isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const
{
	return m_Planes.isHit(ray, minT, maxT, record);
}

bool Box::hasBoundingBox(double time0, double time1, AABB& boundingBox) const
{
	return m_Planes.hasBoundingBox(time0, time1, boundingBox);
}

Point3 Box::getCenter() const
{
	return m_Dimension / 2;
}

Point3 Box::getOrigin() const
{
	return m_Origin;
}

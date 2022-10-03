#ifndef PLANE_H

#define PLANE_H

#include "Hittable.h"
#include "../Materials/Material.h"

#include <memory>

class XYPlane : public Hittable
{
public:
	XYPlane(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> material);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	double m_X0, m_X1;
	double m_Y0, m_Y1;
	double m_K;

	std::shared_ptr<const Material> m_MaterialPtr;
};

class XZPlane : public Hittable
{
public:
	XZPlane(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> material);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	double m_X0, m_X1;
	double m_Z0, m_Z1;
	double m_K;

	std::shared_ptr<const Material> m_MaterialPtr;
};

class YZPlane : public Hittable
{
public:
	YZPlane(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> material);

	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

private:
	double m_Y0, m_Y1;
	double m_Z0, m_Z1;
	double m_K;

	std::shared_ptr<const Material> m_MaterialPtr;
};

#endif // !PLANE_H
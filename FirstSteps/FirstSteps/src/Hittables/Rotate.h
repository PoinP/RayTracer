#ifndef ROTATE_H

#define ROTATE_H

#include "Hittable.h"

#include <memory>

class Rotate : public Hittable
{
public:
	Rotate(std::shared_ptr<Hittable> object, double angle);
	virtual bool isHit(const Ray& ray, double minT, double maxT, HitRecord& record) const override;
	virtual bool hasBoundingBox(double time0, double time1, AABB& boundingBox) const override;
	virtual Point3 getCenter() const override;
	virtual Point3 getOrigin() const override;

protected:
	std::shared_ptr<Hittable> m_Object;
	double m_Angle;
	AABB m_AABBox;
	bool m_HasBox;
	double m_CosTheta;
	double m_SinTheta;


	virtual Vector3 rotate(const Vector3& vector) const = 0;
	virtual Vector3 rotateInverse(const Vector3& vector) const = 0;
};

class RotateX : public Rotate
{
public:
	RotateX(std::shared_ptr<Hittable> object, double angle);

private:
	virtual Vector3 rotate(const Vector3& vector) const override;
	virtual Vector3 rotateInverse(const Vector3& vector) const override;
};

class RotateY : public Rotate
{
public:
	RotateY(std::shared_ptr<Hittable> object, double angle);

private:
	virtual Vector3 rotate(const Vector3& vector) const override;
	virtual Vector3 rotateInverse(const Vector3& vector) const override;
};

class RotateZ : public Rotate
{
public:
	RotateZ(std::shared_ptr<Hittable> object, double angle);

private:
	virtual Vector3 rotate(const Vector3& vector) const override;
	virtual Vector3 rotateInverse(const Vector3& vector) const override;
};

void rotateX(std::shared_ptr<Hittable>& obj, double angle);
void rotateY(std::shared_ptr<Hittable>& obj, double angle);
void rotateZ(std::shared_ptr<Hittable>& obj, double angle);

#endif // !ROTATE_H
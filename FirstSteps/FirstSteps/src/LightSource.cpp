#include "LightSource.h"

#include "Utility.h"
#include "Material.h"

LightSource::LightSource(const Point3& origin, double softness)
    : m_Origin(origin), m_Softness(softness)
{
}

bool LightSource::isInShadow(const Ray& ray, const HitRecord& record, const HittableList& world) const
{
	Vector3 shadowVector = (m_Origin + randomInUnitSphere() * m_Softness) - record.hitPoint;
	Ray shadowRay = Ray(record.hitPoint, shadowVector, ray.time());
	HitRecord dummyRecord;

	bool isReflecting = dotProduct(record.normalVector, ray.direction()) > 0;

	if (isReflecting)
		if (world.isHit(shadowRay, 0.001, INF, dummyRecord))
			if(!dummyRecord.materialPtr->transmit())
				return true;

	return false;
}

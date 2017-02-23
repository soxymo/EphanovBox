#include "Engine/Math/Plane3.hpp"
#include <math.h>


Plane3::Plane3(Vector3 normal, float distance) {
	m_normal = normal;
	m_distToOrigin = distance;
}

Plane3::Plane3(const Plane3& copyPlane) {
	m_normal = copyPlane.m_normal;
	m_distToOrigin = copyPlane.m_distToOrigin;
}

bool Plane3::IsPointOnPlane(Vector3 point) const {
	return DotProduct(point, m_normal) == -m_distToOrigin;
}

bool Plane3::RealIsPointInFront(Vector3 point) const {
	return DotProduct(point, m_normal) > m_distToOrigin;
}

bool Plane3::DoesSphereIntersectPlane(Sphere3 sphere) const {
	float pointDistanceToOrigin = DotProduct(sphere.center, m_normal);
	return fabs(pointDistanceToOrigin) <= m_distToOrigin + sphere.radius;
}

bool Plane3::IsPointInFront(Vector3 point) const {
	return DotProduct(point, m_normal) > 0;
}


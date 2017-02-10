#pragma once
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Sphere3.hpp"


class Plane3 {
public:
	Vector3 m_normal;
	float m_distToOrigin;
	
	Plane3(Vector3 normal, float distance);
	Plane3(const Plane3& copyPlane);
	bool IsPointOnPlane(Vector3 point) const;
	bool DoesSphereIntersectPlane(Sphere3 sphere) const;
	bool IsPointInFront(Vector3 point) const;
};
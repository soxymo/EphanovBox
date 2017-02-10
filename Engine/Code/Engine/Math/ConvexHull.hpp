#pragma once
#include "Engine/Math/Plane3.hpp"
#include <vector>

class ConvexHull {

public:
	std::vector<Plane3> m_boundingPlanes;

	ConvexHull(std::vector<Plane3> boundPlanes);
	bool IsPointInsideHull(Vector3 point) const;
	void AddPlaneToHull(const Plane3& newPlane);

};
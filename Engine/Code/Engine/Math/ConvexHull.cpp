#include "Engine/Math/ConvexHull.hpp"


ConvexHull::ConvexHull(std::vector<Plane3> boundPlanes) {
	m_boundingPlanes = boundPlanes;
}

bool ConvexHull::IsPointInsideHull(Vector3 point) const {
	for (unsigned int i = 0; i < m_boundingPlanes.size(); i++) {
		if (m_boundingPlanes[i].IsPointInFront(point) == false)
			return false;
	}
	return true;
}

void ConvexHull::AddPlaneToHull(const Plane3& newPlane) {
	m_boundingPlanes.push_back(newPlane);
}


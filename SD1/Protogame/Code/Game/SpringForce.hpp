#pragma once
#include "Engine/Math/LineSegment3.hpp"

class SpringForce {
public:
	SpringForce(Vector3 startPoint, Vector3 endPoint, float stiffness, float unstretchedLength);
	Vector3 ComputeForce(const Vector3& startPoint, const Vector3& endPoint);
	void Render() const;

	LineSegment3 line;
	float stiffness;
	float unstretchedLength;

};
#include "Engine/Math/AABB3.hpp"

AABB3::AABB3() {
	min.SetXYZ(0.f, 0.f, 0.f);
	max.SetXYZ(0.f, 0.f, 0.f);
}

AABB3::AABB3(const AABB3& copy) {
	min = copy.min;
	max = copy.max;
}

AABB3::AABB3(const Vector3& mins, const Vector3& maxs) {
	min = mins;
	max = maxs;
}

AABB3::AABB3(const Vector3& center, float radiusX, float radiusY, float radiusZ) {
	Vector3 radiusVector(radiusX, radiusY, radiusZ);
	min = center - radiusVector;
	max = center + radiusVector;
}

void AABB3::StretchToIncludePoint(const Vector3& point) {
	if (point.x > max.x)
		max.x = point.x;
	if (point.y > max.y)
		max.y = point.y;
	if (point.z > max.z)
		max.z = point.z;

	if (point.x < min.x)
		min.x = point.x;
	if (point.y < min.y)
		min.y = point.y;
	if (point.z < min.z)
		min.z = point.z;
}

void AABB3::AddPadding(float xPaddingRadius, float yPaddingRadius, float zPaddingRadius) {
	Vector3 padRadius(xPaddingRadius, yPaddingRadius, zPaddingRadius);
	min -= padRadius;
	max += padRadius;
}

void AABB3::Translate(const Vector3& translation) {
	min += translation;
	max += translation;
}

bool AABB3::IsPointInside(const Vector3& point) const {
	if (point.x > max.x)
		return false;
	if (point.y > max.y)
		return false;
	if (point.z > max.z)
		return false;

	if (point.x < min.x)
		return false;
	if (point.y < min.y)
		return false;
	if (point.z < min.z)
		return false;

	return true;
}

const Vector3 AABB3::CalcSize() const {
	return Vector3(max.x - min.x, max.y - min.y, max.z - min.z);
}

const Vector3 AABB3::CalcCenter() const {
	Vector3 halfSizeVector = CalcSize()*0.5f;
	return min + halfSizeVector;
}

const Vector3 AABB3::GetPointAtNormalizedPositionWithinBox(const Vector3& normalizedPosition) const {
	Vector3 scaleVector = CalcSize() * normalizedPosition;
	return min + scaleVector;
}

const Vector3 AABB3::GetNormalizedPositionForPointWithinBox(const Vector3& point) const {
	Vector3 sizeVector = CalcSize();
	if (sizeVector.x != 0.f && sizeVector.y != 0.f && sizeVector.y != 0.f) {
		Vector3 translatePoint = point - min;
		translatePoint.InverseScaleNonUniform(sizeVector);
		return translatePoint;
	}
	else {
		return Vector3(0.f, 0.f, 0.f);
	}
}

bool DoAABB3sOverlap(const AABB3& a, const AABB3& b) {
	if (a.max.x < b.min.x)
		return false;
	if (a.max.y < b.min.y)
		return false;
	if (a.max.z < b.min.z)
		return false;

	if (a.min.x > b.max.x)
		return false;
	if (a.min.y > b.max.y)
		return false;
	if (a.min.z > b.max.z)
		return false;

	return true;
}

AABB3 Interpolate(const AABB3& start, const AABB3& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	AABB3 blended;
	blended.min = (fractionOfStart * start.min) + (fractionToEnd * end.min);
	blended.max = (fractionOfStart * start.max) + (fractionToEnd * end.max);
	return blended;
}

void AABB3::operator-=(const Vector3& antiTranslation) {
	min -= antiTranslation;
	max -= antiTranslation;
}

void AABB3::operator+=(const Vector3& translation) {
	min += translation;
	max += translation;
}

const AABB3 AABB3::operator-(const Vector3& antiTranslation) const {
	return AABB3(min - antiTranslation, max - antiTranslation);
}

const AABB3 AABB3::operator+(const Vector3& translation) const {
	return AABB3(min + translation, max + translation);
}


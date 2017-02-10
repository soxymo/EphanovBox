#pragma once
#include "Engine/Math/Vector3.hpp"


class AABB3 {
public:
	Vector3 min;
	Vector3 max;
public:
	AABB3();
	AABB3(const AABB3& copy);
	explicit AABB3(const Vector3& mins, const Vector3& maxs);
	explicit AABB3(const Vector3& center, float radiusX, float radiusY, float radiusZ);

	void StretchToIncludePoint(const Vector3& point);
	void AddPadding(float xPaddingRadius, float yPaddingRadius, float zPaddingRadius);
	void Translate(const Vector3& translation);

	bool IsPointInside(const Vector3& point) const;
	const Vector3 CalcSize() const;
	const Vector3 CalcCenter() const;
	const Vector3 GetPointAtNormalizedPositionWithinBox(const Vector3& normalizedPosition) const;
	const Vector3 GetNormalizedPositionForPointWithinBox(const Vector3& point) const;

	const AABB3 operator + (const Vector3& translation) const;
	const AABB3 operator - (const Vector3& antiTranslation) const;
	void operator += (const Vector3& translation);
	void operator -= (const Vector3& antiTranslation);

	friend AABB3 Interpolate(const AABB3& start, const AABB3& end, float fractionToEnd);
	friend bool DoAABB3sOverlap(const AABB3& a, const AABB3& b);
};
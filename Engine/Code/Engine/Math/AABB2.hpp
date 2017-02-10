#pragma once
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vertex3.hpp"

class AABB2 {
public:
	Vector2 min;
	Vector2 max;
public:
	~AABB2() {}
	AABB2() {}
	AABB2(const AABB2& copy);
	explicit AABB2(float initialX, float initialY);
	explicit AABB2(float minX, float minY, float maxX, float maxY);
	explicit AABB2(const Vector2& mins, const Vector2& maxs);
	explicit AABB2(const Vector2& center, float radiusX, float radiusY);

	void StretchToIncludePoint(const Vector2& point);
	void AddPadding(float xPaddingRadius, float yPaddingRadius);
	void Translate(const Vector2& translation);

	bool IsPointInside(const Vector2& point) const;
	const Vector2 CalcSize() const;
	const Vector2 CalcCenter() const;
	const Vector2 GetPointAtNormalizedPositionWithinBox(const Vector2& normalizedPosition) const;
	const Vector2 GetNormalizedPositionForPointWithinBox(const Vector2& point) const;
	void GetCornersTopLeftOrigin(Vector2& bottomLeft, Vector2& bottomRight, Vector2& topRight, Vector2& topLeft);
	void GetCornerArrayWithTopLeftOrigin(Vector2* fourVecArray);


	const AABB2 operator + (const Vector2& translation) const;
	const AABB2 operator - (const Vector2& antiTranslation) const;
	void operator += (const Vector2& translation);
	void operator -= (const Vector2& antiTranslation);

	friend AABB2 Interpolate(const AABB2& start, const AABB2& end, float fractionToEnd);

};
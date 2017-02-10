#pragma once
#include "Vector2.hpp"

class Disc2 {
public:
	Vector2 center;
	float radius;
	static const Disc2 UNIT_CIRCLE; 

	~Disc2() {}
	Disc2() { radius = 0; }
	Disc2(const Disc2& copy);
	explicit Disc2(float initialX, float initialY, float initialRadius);
	explicit Disc2(const Vector2& initialCenter, float initialRadius);

	void StretchToIncludePoint(const Vector2& point);
	void AddPadding(float paddingRadius);
	void Translate(const Vector2& translation);

	bool IsPointInside(const Vector2& point) const;

	const Disc2 operator + (const Vector2& translation) const;
	const Disc2 operator - (const Vector2& antiTranslation) const;
	void operator += (const Vector2& translation);
	void operator -= (const Vector2& antiTranslation);

	friend const Disc2 Interpolate(const Disc2& start, const Disc2& end, float fractionToEnd);


};
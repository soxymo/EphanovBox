#pragma once
#include "Engine/Math/Vector3.hpp"

class Sphere3 {
public:
	Vector3 center;
	float radius;
	static const  Sphere3 UNIT_CIRCLE3D;
	Sphere3();
	Sphere3(const Sphere3& copy);
	explicit Sphere3(float initialX, float initialY, float initialZ, float initialRadius);
	explicit Sphere3(const Vector3& intialCenter, float initialRadius);

	void StretchToIncludePoint(const Vector3& point);
	void AddPadding(float paddingRadius);
	void Translate(const Vector3& point);

	bool IsPointInside(const Vector3& point) const;
	Vector3 GetRandomPointInsideShpere() const;

	const Sphere3 operator + (const Vector3& translation) const;
	const Sphere3 operator - (const Vector3& antiTranslation) const;
	void operator += (const Vector3& translation);
	void operator -= (const Vector3& antiTranslation);
	friend const Sphere3 Interpolate(const Sphere3& start, const Sphere3& end, float fractionToEnd);
	friend bool DoSpheresOverlap(const Sphere3& a, const Sphere3& b);
};
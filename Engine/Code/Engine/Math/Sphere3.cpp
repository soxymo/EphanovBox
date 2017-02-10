#include "Engine/Math/Sphere3.hpp"
#include "Engine/Math/MathUtils.hpp"

Sphere3::Sphere3() {
	radius = 0;
	center.SetXYZ(0.f, 0.f, 0.f);
}

Sphere3::Sphere3(const Sphere3& copy) {
	center = copy.center;
	radius = copy.radius;
}

Sphere3::Sphere3(float initialX, float initialY, float initialZ, float initialRadius) {
	center.SetXYZ(initialX, initialY, initialZ);
	radius = initialRadius;
}

Sphere3::Sphere3(const Vector3& intialCenter, float initialRadius) {
	center = intialCenter;
	radius = initialRadius;
}

void Sphere3::StretchToIncludePoint(const Vector3& point) {
	radius = CalcDistance(center, point);
}

void Sphere3::AddPadding(float paddingRadius) {
	radius += paddingRadius;
}

void Sphere3::Translate(const Vector3& translation) {
	center += translation;
}

bool Sphere3::IsPointInside(const Vector3& point) const {
	if (CalcDistance(center, point) < radius)
		return true;
	return false;
}

Vector3 Sphere3::GetRandomPointInsideShpere() const {
	float xMod;
	float yMod;
	float zMod;

	do {
		xMod = GetRandomFloatInRange(-radius, radius);
		yMod = GetRandomFloatInRange(-radius, radius);
		zMod = GetRandomFloatInRange(-radius, radius);
	} while ((xMod*xMod) + (yMod*yMod) + (zMod*zMod) > (radius*radius));

	return Vector3(center.x + xMod, center.y + yMod,center.z + zMod);
}

bool DoSpheresOverlap(const Sphere3& a, const Sphere3& b) {
	float totalRadius = a.radius + b.radius;
	if (CalcDistanceSquared(a.center, b.center)< totalRadius*totalRadius) {
		return true;
	}
	return false;
}

const Sphere3 Interpolate(const Sphere3& start, const Sphere3& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	Sphere3 blended;
	blended.center = (fractionOfStart * start.center) + (fractionToEnd * end.center);
	blended.radius = (fractionOfStart * start.radius) + (fractionToEnd * end.radius);
	return blended;
}

void Sphere3::operator-=(const Vector3& antiTranslation) {
	center -= antiTranslation;
}

void Sphere3::operator+=(const Vector3& translation) {
	center += translation;
}

const Sphere3 Sphere3::operator-(const Vector3& antiTranslation) const {
	return Sphere3(center - antiTranslation, radius);
}

const Sphere3 Sphere3::operator+(const Vector3& translation) const {
	return Sphere3(center + translation, radius);
}


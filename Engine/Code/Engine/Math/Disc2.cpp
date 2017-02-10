#include "Disc2.hpp"


Disc2::Disc2(const Disc2& copy){
	center = copy.center;
	radius = copy.radius;

}

Disc2::Disc2(float initialX, float initialY, float initialRadius){
	center = Vector2(initialX, initialY);
	radius = initialRadius;
}

Disc2::Disc2(const Vector2& initialCenter, float initialRadius){
	center = initialCenter;
	radius = initialRadius;
}

void Disc2::StretchToIncludePoint(const Vector2& point){
	radius = CalcDistance(center, point);
}

void Disc2::AddPadding(float paddingRadius){
	radius += paddingRadius;
}

void Disc2::Translate(const Vector2& translation){
	center += translation;
}

bool Disc2::IsPointInside(const Vector2& point) const{
	if (CalcDistance(center, point) < radius)
		return true;
	return false;
}

const Disc2 Interpolate(const Disc2& start, const Disc2& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	Disc2 blended;
	blended.center = (fractionOfStart * start.center) + (fractionToEnd * end.center);
	blended.radius = (fractionOfStart * start.radius) + (fractionToEnd * end.radius);
	return blended;
}

void Disc2::operator-=(const Vector2& antiTranslation) {
	center -= antiTranslation;
}

void Disc2::operator+=(const Vector2& translation) {
	center += translation;
}

const Disc2 Disc2::operator-(const Vector2& antiTranslation) const {
	return Disc2(center.x - antiTranslation.x, center.y - antiTranslation.y, radius);
}

const Disc2 Disc2::operator+(const Vector2& translation) const {
	return Disc2(center.x + translation.x, center.y + translation.y, radius);
}

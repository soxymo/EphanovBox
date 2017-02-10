#include "AABB2.hpp"

AABB2::AABB2(float initialX, float initialY){
	min.x = initialX;
	min.y = initialY;
	max.x = initialX + 1;
	max.y = initialY + 1;
}

AABB2::AABB2(const AABB2& copy){
	min = copy.min;
	max = copy.max;
}

AABB2::AABB2(float minX, float minY, float maxX, float maxY){
	min.x = minX;
	min.y = minY;
	max.x = maxX;
	max.y = maxY;
}

AABB2::AABB2(const Vector2& mins, const Vector2& maxs){
	min = mins;
	max = maxs;
}

AABB2::AABB2(const Vector2& center, float radiusX, float radiusY){
	Vector2 radVector(radiusX, radiusY);
	min = center - radVector;
	max = center + radVector;
}

void AABB2::StretchToIncludePoint(const Vector2& point){
	if(point.x > max.x)
		max.x = point.x;
	if(point.y > max.y)
		max.y = point.y;
	if(point.x < min.x)
		min.x = point.x;
	if(point.y < min.y)
		min.y = point.y;
}

void AABB2::AddPadding(float xPaddingRadius, float yPaddingRadius){
	Vector2 padRadius = Vector2(xPaddingRadius, yPaddingRadius);
	min -= padRadius;
	max += padRadius;
}

void AABB2::Translate(const Vector2& translation){
	min += translation;
	max += translation;
}

bool AABB2::IsPointInside(const Vector2& point) const{
	if (point.x > max.x)
		return false;
	if (point.y > max.y)
		return false;
	if (point.x < min.x)
		return false;
	if (point.y < min.y)
		return false;

	return true;
}

const Vector2 AABB2::CalcSize() const{
	return Vector2(max.x - min.x, max.y - min.y);
}

const Vector2 AABB2::CalcCenter() const{
	Vector2 halfSizeVector = CalcSize() * 0.5;
	return Vector2(min.x + halfSizeVector.x, min.y + halfSizeVector.y);
}

const Vector2 AABB2::GetPointAtNormalizedPositionWithinBox(const Vector2& normalizedPosition) const{
	Vector2 scaleVector = CalcSize() * normalizedPosition;
	return Vector2(min.x + scaleVector.x, min.y + scaleVector.y);
	
}

const Vector2 AABB2::GetNormalizedPositionForPointWithinBox(const Vector2& point) const{
	Vector2 sizeVector = CalcSize();
	if (sizeVector.x != 0 && sizeVector.y != 0) {
		Vector2 translatePoint(point.x - min.x, point.y - min.y);
		return Vector2(translatePoint.x / sizeVector.x, translatePoint.y / sizeVector.y);
	}
	else { //Point isn't actually inside the box;
		return Vector2(0.f, 0.f);
	}
	
}

void AABB2::GetCornersTopLeftOrigin(Vector2& bottomLeft, Vector2& bottomRight, Vector2& topRight, Vector2& topLeft) {
	bottomLeft.SetXY(min.x, max.y);
	bottomRight.SetXY(max.x, max.y);
	topRight.SetXY(max.x, min.y);
	topLeft.SetXY(min.x, min.y);
}

void AABB2::GetCornerArrayWithTopLeftOrigin(Vector2* fourVecArray) {
	fourVecArray[0].SetXY(min.x, max.y);
	fourVecArray[1].SetXY(max.x, max.y);
	fourVecArray[2].SetXY(max.x, min.y);
	fourVecArray[3].SetXY(min.x, min.y);
}

AABB2 Interpolate(const AABB2& start, const AABB2& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	AABB2 blended;
	blended.min = (fractionOfStart * start.min) + (fractionToEnd * end.min);
	blended.max = (fractionOfStart * start.max) + (fractionToEnd * end.max);
	return blended;
}

void AABB2::operator-=(const Vector2& antiTranslation) {
	min -= antiTranslation;
	max -= antiTranslation;
}

void AABB2::operator+=(const Vector2& translation){
	min += translation;
	max += translation;
}

const AABB2 AABB2::operator-(const Vector2& antiTranslation) const{
	return AABB2(min - antiTranslation, max - antiTranslation);
}

const AABB2 AABB2::operator+(const Vector2& translation) const{
	return AABB2(min + translation, max + translation);
}

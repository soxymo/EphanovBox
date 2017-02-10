#include "Engine/Math/LineSegment3.hpp"



LineSegment3::LineSegment3() {
	start.SetXYZ(0.f, 0.f, 0.f);
	end.SetXYZ(0.f, 0.f, 0.f);
}

LineSegment3::LineSegment3(const Vector3& starting, const Vector3& ending) {
	start = starting;
	end = ending;
}

LineSegment3::LineSegment3(float startX, float startY, float startZ, float endX, float endY, float endZ) {
	start.SetXYZ(startX, startY, startZ);
	end.SetXYZ(endX, endY, endZ);
}

void LineSegment3::SetStart(const Vector3& starting) {
	start = starting;
}

void LineSegment3::SetEnd(const Vector3& ending) {
	end = ending;
}

void LineSegment3::TranslateLine(const Vector3& translation) {
	start += translation;
	end += translation;
}

void LineSegment3::TranslateStart(const Vector3& translation) {
	start += translation;
}

void LineSegment3::TranslateEnd(const Vector3& translation) {
	end += translation;
}

void LineSegment3::ReverseLineDirection() {
	Vector3 tempStart = start;
	start = end;
	end = tempStart;
}

float LineSegment3::CalcLength() {
	return CalcDistance(start, end);
}


float LineSegment3::CalcSlope() {
	if (end.x - start.x == 0.f)
		return 0.f;
	return (end.y - start.y) / (end.x - start.x);
}

const Vector3 LineSegment3::CalcPointFromPercentageToEnd(float percentage) {
	Vector3  scalingVector = end - start;
	scalingVector.SetLength(scalingVector.CalcLength()*percentage);
	return scalingVector + start;
}

const LineSegment3 Interpolate(const LineSegment3& start, const LineSegment3& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	LineSegment3 blended;
	blended.start = (fractionOfStart * start.start) + (fractionToEnd * end.start);
	blended.end = (fractionOfStart * start.end) + (fractionToEnd * end.end);
	return blended;
}

void LineSegment3::operator+=(const Vector3& translation) {
	start += translation;
	end += translation;
}

void LineSegment3::operator-=(const Vector3& antiTranslation) {
	start -= antiTranslation;
	end -= antiTranslation;
}

const LineSegment3 LineSegment3::operator-(const Vector3& antiTranslation) {
	return LineSegment3(start - antiTranslation, end - antiTranslation);
}

const LineSegment3 LineSegment3::operator+(const Vector3& translation) {
	return LineSegment3(start + translation, end + translation);
}

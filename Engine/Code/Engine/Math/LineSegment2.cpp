#include "LineSegment2.hpp"

LineSegment2::LineSegment2(Vector2 starting, Vector2 ending) {
	start = starting;
	end = ending;
}

LineSegment2::LineSegment2(float startX, float startY, float endX, float endY) {
	start = Vector2(startX, startY);
	end = Vector2(endX, endY);
}

void LineSegment2::SetStart(const Vector2 starting) {
	start = starting;
}

void LineSegment2::SetEnd(const Vector2 ending) {
	end = ending;
}

void LineSegment2::TranslateLine(const Vector2& translation) {
	end += translation;
	start += translation;
}

void LineSegment2::TranslateStart(const Vector2& translation) {
	start += translation;
}

void LineSegment2::TranslateEnd(const Vector2& translation) {
	end += translation;
}

void LineSegment2::ReverseLineDirection() {
	Vector2 tempStart = start;
	start = end;
	end = tempStart;
}


float LineSegment2::CalcLength() {
	return CalcDistance(start, end);
}

float LineSegment2::CalcHeading() {
	return Vector2(end.x - start.x, end.y - start.y).CalcHeadingDegrees();
}

float LineSegment2::CalcReverseHeading() {
	Vector2 reverseVector = end - start;
	reverseVector.Rotate90Degrees();
	reverseVector.Rotate90Degrees();
	return reverseVector.CalcHeadingDegrees();
}

float LineSegment2::CalcSlope() {
	if (end.x - start.x == 0)
		return 0.f;
	return(end.y - start.y) / (end.x - start.x);
}

const Vector2 LineSegment2::CalcPointFromPercentageToEnd(float percentage) {
	Vector2 scalingVector = end - start;
	scalingVector.SetLength(scalingVector.CalcLength()*percentage);
	return scalingVector + start; 
}


const LineSegment2 Interpolate(const LineSegment2& start, const LineSegment2& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	LineSegment2 blended;
	blended.start = (fractionOfStart * start.start) + (fractionToEnd * end.start);
	blended.end = (fractionOfStart * start.end) + (fractionToEnd * end.end);
	return blended;
}

void LineSegment2::operator-=(const Vector2& antiTranslation) {
	start -= antiTranslation;
	end -= antiTranslation;
}

void LineSegment2::operator+=(const Vector2& translation) {
	start += translation;
	end += translation;
}

const LineSegment2 LineSegment2::operator-(const Vector2& antiTranslation) {
	return LineSegment2(start - antiTranslation, end - antiTranslation);
}

const LineSegment2 LineSegment2::operator+(const Vector2& translation) {
	return LineSegment2(start + translation, end + translation);
}

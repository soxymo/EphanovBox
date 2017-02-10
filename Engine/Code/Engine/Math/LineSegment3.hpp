#pragma once
#include "Vector3.hpp"


class LineSegment3 {
public:
	Vector3 start;
	Vector3 end;
public:
	LineSegment3();
	explicit LineSegment3(const Vector3& starting, const Vector3& ending);
	explicit LineSegment3(float startX, float startY, float startZ, float endX, float endY, float endZ);

	void SetStart(const Vector3& starting);
	void SetEnd(const Vector3& ending);
	void TranslateLine(const Vector3& translation);
	void TranslateStart(const Vector3& translation);
	void TranslateEnd(const Vector3& translation);
	void ReverseLineDirection();

	float CalcLength();
	//float CalcHeadingDegrees();
	float CalcSlope();
	const Vector3 CalcPointFromPercentageToEnd(float percentage);

	const LineSegment3 operator + (const Vector3& translation);
	const LineSegment3 operator - (const Vector3& antiTranslation);

	void operator += (const Vector3& translation);
	void operator -= (const Vector3& antiTranslation);
	friend const LineSegment3 Interpolate(const LineSegment3& start, const LineSegment3& end, float fractionToEnd);
};
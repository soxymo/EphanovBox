#pragma once
#include "Vector2.hpp"

class LineSegment2 {
public:
	Vector2 start;
	Vector2 end;

	LineSegment2() {};
	~LineSegment2() {};
	explicit LineSegment2(Vector2 starting, Vector2 ending);
	explicit LineSegment2(float startX, float startY, float endX, float endY);

	void SetStart(const Vector2 starting);
	void SetEnd(const Vector2 ending);
	void TranslateLine(const Vector2& translation);
	void TranslateStart(const Vector2& translation);
	void TranslateEnd(const Vector2& translation);
	void ReverseLineDirection();

	float CalcLength();
	float CalcHeading();
	float CalcReverseHeading();
	float CalcSlope();
	const Vector2 CalcPointFromPercentageToEnd(float percentage);

	const LineSegment2 operator + (const Vector2& translation);
	const LineSegment2 operator - (const Vector2& antiTranslation);

	void operator += (const Vector2& translation);
	void operator -= (const Vector2& antiTranslation);
	friend const LineSegment2 Interpolate(const LineSegment2& start, const LineSegment2& end, float fractionToEnd);
};
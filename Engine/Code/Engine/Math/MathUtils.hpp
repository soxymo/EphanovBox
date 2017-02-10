#pragma once


const float fTWO_PI= 6.283185307179586476f;

float CosDegrees(float degrees);
float SinDegrees(float degrees);
float Atan2Degrees(float y, float x);
float ConvertRadiansToDegrees(float radians);
float ConvertDegreesToRadians(float degrees);
int GetRandomIntLessThan(int maxValueNotInclusive);
int GetRandomIntInRange(int minValueInclusive, int maxValueInclusive);
float GetRandomFloatZeroToOne();
float GetRandomFloatInRange(float minimumInclusive, float maximumInclusive);
float RangeMapFloat(float inValue, float inMin, float inMax, float outMin, float outMax);
float CalcDistanceBetweenAnglesDegrees(float startAngle, float endAngle);
float FastFloor(float val);
float SmoothStep(float inputZeroToOne);
float SmoothStep5(float inputZeroToOne);

template< typename T>
const T& ClampWithin(const T& value, const T& min, const T& max) {
	if (value < min)
		return min;
	if (value > max)
		return max;

	return value;
}







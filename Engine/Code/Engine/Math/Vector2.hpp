#pragma once //always include this first in headers

class Vector2 {
public:
	float x;
	float y;

public:
	Vector2();//do nothing for speed!
	explicit Vector2(float xVal, float yVal);
	Vector2(const Vector2& copy);

	const float* GetAsFloatArray() const;
	float* GetAsFloatArray();
	float CalcLength() const;
	float CalcLengthSquared() const;
	float CalcHeadingDegrees() const;
	float CalcHeadingRadians() const;

	void SetXY(float newX, float newY);
	void Rotate90Degrees();
	void RotateNegative90Degrees();
	void RotateDegrees(float degrees);
	void RotateRadians(float radians);
	float Normalize();
	float SetLength(float newLength);
	void ScaleUniform(float scale);
	void ScaleNonUniform(const Vector2& perAxisScaleFactors);
	void InverseScaleNonUniform(const Vector2& perAxisDivisors);
	void SetHeadingDegrees(float headingDegrees);
	void SetHeadingRadians(float headingRadians);
	void SetUnitLengthAndHeadingDegrees(float headingDegrees);
	void SetUnitLengthAndHeadingRadians(float headingRadians);
	void SetLengthAndHeadingDegrees(float newLength, float headingDegrees);
	void SetLengthAndHeadingRadians(float newLength, float headingRadians);
	

	bool operator == (const Vector2& vectorToEqual) const;
	bool operator != (const Vector2& vectorToNotEqual) const;
	const Vector2 operator + (const Vector2& vectorToAdd) const;
	const Vector2 operator - (const Vector2& vectorToSubtract) const;
	const Vector2 operator * (float scale) const;
	const Vector2 operator * (const Vector2& perAxisScaleFactors) const;
	const Vector2 operator / (float inverseScale) const;
	void operator *= (float scale);
	void operator *= (const Vector2& perAxisScaleFactors);
	void operator += (const Vector2& vectorToAdd);
	void operator -= (const Vector2& vectorToSubtract);

	friend float CalcDistance(const Vector2& positionA, const Vector2& positionB);
	friend float CalcDistanceSquared(const Vector2& posA, const Vector2& posB);
	friend const Vector2 operator * (float scale, const Vector2& vectorToScale);
	friend float DotProduct(const Vector2& a, const Vector2& b);
	friend Vector2 Interpolate(const Vector2& start, const Vector2& end, float fractionToEnd);

};
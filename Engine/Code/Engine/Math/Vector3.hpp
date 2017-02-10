#pragma once


class Vector3 {
public:
	float x;
	float y;
	float z;

public:
	Vector3() {};
	explicit Vector3(float xVal, float yVal, float zVal);
	Vector3(const Vector3& copy);

	const float* GetAsFloatArray() const;
	float* GetAsFloatArray();
	float CalcLength() const;
	float CalcLengthSquared() const;
	float CalcLengthInXYSquared() const;

	void SetXYZ(float newX, float newY, float newZ);
	float Normalize();
	float SetLength(float newLength);
	void ScaleUniform(float scale);
	void ScaleNonUniform(const Vector3& perAxisScaleFactors);
	void InverseScaleNonUniform(const Vector3& perAxisDivisors);

	bool operator == (const Vector3& vectorToEqual) const;
	bool operator != (const Vector3& vectorToNotEqual) const;
	const Vector3 operator + (const Vector3& vectorToAdd) const;
	const Vector3 operator - (const Vector3& vectorToSubtract) const;
	const Vector3 operator * (float scale) const;
	const Vector3 operator * (const Vector3& perAxisScaleFactors) const;
	const Vector3 operator / (float inverseScale) const;
	void operator *= (float scale);
	void operator *= (const Vector3& perAxisScaleFactors);
	void operator += (const Vector3& vectorToAdd);
	void operator -= (const Vector3& vectorToSubtract);

	friend float CalcDistance(const Vector3& positionA, const Vector3& positionB);
	friend float CalcDistanceSquared(const Vector3& posA, const Vector3& posB);
	friend const Vector3 operator * (float scale, const Vector3& vectorToScale);
	friend float DotProduct(const Vector3& a, const Vector3& b);
	friend Vector3 Interpolate(const Vector3& start, const Vector3& end, float fractionToEnd);
};
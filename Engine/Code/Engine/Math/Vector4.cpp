#include "Engine/Math/Vector4.hpp"
#include <math.h>


Vector4::Vector4(float xVal, float yVal, float zVal, float wVal) {
	x = xVal;
	y = yVal;
	z = zVal;
	w = wVal;

}

Vector4::Vector4(const Vector4& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
	w = copy.w;
}

const float* Vector4::GetAsFloatArray() const {
	return &x;
}

float* Vector4::GetAsFloatArray() {
	return &x;
}

float Vector4::CalcLength() const {
	return (float)sqrt((x*x) + (y*y) + (z*z) + (w*w));
}

float Vector4::CalcLengthSquared() const {
	return (x*x) + (y*y) + (z*z) + (w*w);
}

void Vector4::SetXYZW(float newX, float newY, float newZ, float newW) {
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

float Vector4::Normalize() {
	float length = CalcLength();
	if (length != 0.f) {
		float invLength = 1.f / length;
		x = x*invLength;
		y = y*invLength;
		z = z*invLength;
		w = w*invLength;
	}
	return length;
}

float Vector4::SetLength(float newLength) {
	float oldLength = CalcLength();
	if (oldLength == 0.f)
		return 0.f;
	float scale = newLength / oldLength;
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
	return oldLength;
}

void Vector4::ScaleUniform(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
}

void Vector4::ScaleNonUniform(const Vector4& perAxisScaleFactors) {
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.z;
	w *= perAxisScaleFactors.w;
}

void Vector4::InverseScaleNonUniform(const Vector4& perAxisDivisors) {
	if (perAxisDivisors.x == 0)
		x = 0;
	else
		x *= 1 / perAxisDivisors.x;

	if (perAxisDivisors.y == 0)
		y = 0;
	else
		y *= 1 / perAxisDivisors.y;

	if (perAxisDivisors.z == 0)
		z = 0;
	else
		z *= 1 / perAxisDivisors.z;

	if (perAxisDivisors.w == 0)
		w = 0;
	else
		w *= 1 / perAxisDivisors.w;
}



void Vector4::operator*=(const Vector4& perAxisScaleFactors) {
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.x;
	w *= perAxisScaleFactors.w;
}

void Vector4::operator-=(const Vector4& vectorToSubtract) {
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
	z -= vectorToSubtract.z;
	w -= vectorToSubtract.w;
}

void Vector4::operator+=(const Vector4& vectorToAdd) {
	x += vectorToAdd.x;
	y += vectorToAdd.y;
	z += vectorToAdd.z;
	w += vectorToAdd.w;
}

void Vector4::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
}

const Vector4 Vector4::operator/(float inverseScale) const {
	if (inverseScale == 0) {
		return Vector4(0.f, 0.f, 0.f, 0.f);
	}
	else {
		float inverse = 1.f / inverseScale;
		return Vector4(inverse*x, inverse*y, inverse*y, inverse*w);
	}
}

const Vector4 Vector4::operator*(const Vector4& perAxisScaleFactors) const {
	return Vector4(x*perAxisScaleFactors.x, y*perAxisScaleFactors.y, z*perAxisScaleFactors.z, w*perAxisScaleFactors.w);
}

const Vector4 Vector4::operator*(float scale) const {
	return Vector4(x*scale, y*scale, z*scale, w*scale);
}

const Vector4 Vector4::operator-(const Vector4& vectorToSubtract) const {
	return Vector4(x - vectorToSubtract.x, y - vectorToSubtract.y, z - vectorToSubtract.z, w - vectorToSubtract.w);
}

const Vector4 Vector4::operator+(const Vector4& vectorToAdd) const {
	return Vector4(x + vectorToAdd.x, y + vectorToAdd.y, z + vectorToAdd.z, w+ vectorToAdd.w);
}

bool Vector4::operator!=(const Vector4& vectorToNotEqual) const {
	return (x != vectorToNotEqual.x) || (y != vectorToNotEqual.y) || (z != vectorToNotEqual.z) || (w != vectorToNotEqual.w);
}

bool Vector4::operator==(const Vector4& vectorToEqual) const {
	return (x == vectorToEqual.x) && (y == vectorToEqual.y) && (z == vectorToEqual.z);
}

float CalcDistanceSquared(const Vector4& posA, const Vector4& posB) {
	Vector4 diffVector = posB - posA;
	return (diffVector.x*diffVector.x) + (diffVector.y *diffVector.y) + (diffVector.z*diffVector.z) + (diffVector.w*diffVector.w);
}

float CalcDistance(const Vector4& positionA, const Vector4& positionB) {
	Vector4 diffVector = positionB - positionA;
	return (float)sqrt((diffVector.x*diffVector.x) + (diffVector.y *diffVector.y) + (diffVector.z*diffVector.z) + (diffVector.w*diffVector.w));
}

const Vector4 operator * (float scale, const Vector4& vectorToScale) {
	return vectorToScale*scale;
}

float DotProduct(const Vector4& a, const Vector4& b) {
	return (a.x*b.x) + (a.y*b.y) + (a.z*b.z) + (a.w*b.w);
}

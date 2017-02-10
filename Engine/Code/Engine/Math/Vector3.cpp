#include "Engine/Math/Vector3.hpp"
#include <math.h>

Vector3::Vector3(float xVal, float yVal, float zVal) {
	x = xVal;
	y = yVal;
	z = zVal;
}

Vector3::Vector3(const Vector3& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

const float* Vector3::GetAsFloatArray() const {
	return &x;
}

float* Vector3::GetAsFloatArray() {
	return &x;
}

float Vector3::CalcLength() const {
	return (float)sqrt((x*x) + (y*y) + (z*z));
}

float Vector3::CalcLengthSquared() const {
	return (x*x) + (y*y) + (z*z);
}

float Vector3::CalcLengthInXYSquared() const {
	return (x*x) + (y*y);
}

void Vector3::SetXYZ(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

float Vector3::Normalize() {
	float length = CalcLength();
	if (length != 0.f) {
		float invLength = 1.f / length;
		x = x*invLength;
		y = y*invLength;
		z = z*invLength;
	}
	return length;
}

float Vector3::SetLength(float newLength) {
	float oldLength = CalcLength();
	if (oldLength == 0.f)
		return 0.f;
	float scale = newLength / oldLength;
	x *= scale;
	y *= scale;
	z *= scale;
	return oldLength;
}

void Vector3::ScaleUniform(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3::ScaleNonUniform(const Vector3& perAxisScaleFactors) {
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.z;
}

void Vector3::InverseScaleNonUniform(const Vector3& perAxisDivisors) {
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
}

Vector3 Interpolate(const Vector3& start, const Vector3& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	Vector3 blended;
	blended = (fractionOfStart * start) + (fractionToEnd * end);
	return blended;
}

void Vector3::operator-=(const Vector3& vectorToSubtract) {
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
	z -= vectorToSubtract.z;
}

void Vector3::operator+=(const Vector3& vectorToAdd) {
	x += vectorToAdd.x;
	y += vectorToAdd.y;
	z += vectorToAdd.z;
}

void Vector3::operator*=(const Vector3& perAxisScaleFactors) {
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
	z *= perAxisScaleFactors.x;
}

void Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

const Vector3 Vector3::operator/(float inverseScale) const {
	if (inverseScale == 0){
		return Vector3(0.f, 0.f, 0.f);
	}
	else {
		float inverse = 1.f / inverseScale;
		return Vector3(inverse*x, inverse*y, inverse*z);
	}
}

const Vector3 Vector3::operator*(const Vector3& perAxisScaleFactors) const {
	return Vector3(x*perAxisScaleFactors.x, y*perAxisScaleFactors.y, z*perAxisScaleFactors.z);
}

const Vector3 Vector3::operator*(float scale) const {
	return Vector3(x*scale, y*scale, z*scale);
}

const Vector3 Vector3::operator-(const Vector3& vectorToSubtract) const {
	return Vector3(x - vectorToSubtract.x, y - vectorToSubtract.y, z - vectorToSubtract.z);
}

const Vector3 Vector3::operator+(const Vector3& vectorToAdd) const {
	return Vector3(x + vectorToAdd.x, y + vectorToAdd.y, z + vectorToAdd.z);
}

bool Vector3::operator!=(const Vector3& vectorToNotEqual) const {
	return (x != vectorToNotEqual.x) || (y != vectorToNotEqual.y) || (z != vectorToNotEqual.z);
}

bool Vector3::operator==(const Vector3& vectorToEqual) const {
	return (x == vectorToEqual.x) && (y == vectorToEqual.y) && (z == vectorToEqual.z);
}


float CalcDistanceSquared(const Vector3& posA, const Vector3& posB) {
	Vector3 diffVector = posB - posA;
	return (diffVector.x*diffVector.x) + (diffVector.y *diffVector.y) + (diffVector.z*diffVector.z);
}

float CalcDistance(const Vector3& positionA, const Vector3& positionB) {
	Vector3 diffVector = positionB - positionA;
	return (float)sqrt((diffVector.x*diffVector.x) + (diffVector.y *diffVector.y) + (diffVector.z*diffVector.z));
}

const Vector3 operator * (float scale, const Vector3& vectorToScale) {
	return vectorToScale*scale;
}

float DotProduct(const Vector3& a, const Vector3& b) {
	return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

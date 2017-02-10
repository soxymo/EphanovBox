#include "Engine/Math/Vector2.hpp" 
#include <math.h>
#include "Engine/Math/MathUtils.hpp"

const float PI = 3.1415926535897932384626f;

Vector2::Vector2(){
	x = 0.f;
	y = 0.f;

}

Vector2::Vector2(float xVal, float yVal){
	x = (float) xVal;
	y = (float) yVal;
}

Vector2::Vector2(const Vector2& copy){
	x = copy.x;
	y = copy.y;
}

const float* Vector2::GetAsFloatArray() const {
	/*float* vectorArrayPntr = new float[2];
	vectorArrayPntr[0] = x;
	vectorArrayPntr[1] = y;
	return vectorArrayPntr;*/
	return &x; //Squirrels method
}

float* Vector2::GetAsFloatArray(){
	/*float* vectorArrayPntr = new float[2];
	vectorArrayPntr[0] = x;
	vectorArrayPntr[1] = y;
	return vectorArrayPntr;*/
	return &x; //Squirrel's method
}

float Vector2::CalcLength() const{
	return (float) sqrt((x*x) + (y*y));
}

float Vector2::CalcLengthSquared() const{
	return (x*x) + (y*y);
}

float Vector2::CalcHeadingDegrees() const{
	return (float) atan2(y, x) * (180.f/PI);

}

float Vector2::CalcHeadingRadians() const{
	return (float) atan2(y, x);
}


//-----------Mutators-------------------


void Vector2::SetXY(float newX, float newY){
	x = newX;
	y = newY;
}

void Vector2::Rotate90Degrees(){
	float temp = x;
	x = -1 * y;
	y = temp;
}

void Vector2::RotateNegative90Degrees(){
	float temp = y;
	y = -1 * x;
	x = temp;
}

void Vector2::RotateDegrees(float degrees){
	float radius = CalcLength();
	float theta = CalcHeadingDegrees();
	theta += degrees;
	float radianTheta = ConvertDegreesToRadians(theta);
	x = (float)(radius*cos(radianTheta));
	y = (float)(radius*sin(radianTheta));
}

void Vector2::RotateRadians(float radians){
	float radius = CalcLength();
	float theta = CalcHeadingRadians();
	theta += radians;
	x = (float)(radius*cos(theta));
	y = (float)(radius*sin(theta));
}

float Vector2::Normalize(){
	float length = CalcLength();
	if (length != 0.f) {
		float invLength = 1.f / length;
		x = x * invLength;
		y = y * invLength;
	}
	return length;
}

float Vector2::SetLength(float newLength){
	float oldLength = CalcLength();
	if (oldLength == 0.f)
		return 0.f;
	float scale = newLength / oldLength;
	x *= scale;
	y *= scale;
	return oldLength;
}

void Vector2::ScaleUniform(float scale){
	x *= scale;
	y *= scale;
}

void Vector2::ScaleNonUniform(const Vector2& perAxisScaleFactors){
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
}

void Vector2::InverseScaleNonUniform(const Vector2& perAxisDivisors){
	if (perAxisDivisors.x == 0)
		x = 0;
	else
		x *= 1 / perAxisDivisors.x;

	if (perAxisDivisors.y == 0)
		y = 0;
	else
		y *= 1 / perAxisDivisors.y;

}

void Vector2::SetHeadingDegrees(float headingDegrees){
	float radius = CalcLength();
	float radiansTheta = ConvertDegreesToRadians(headingDegrees);
	x = (float)(radius*cos(radiansTheta));
	y = (float)(radius* sin(radiansTheta));

}

void Vector2::SetHeadingRadians(float headingRadians){
	float radius = CalcLength();
	x = radius * (float)(cos(headingRadians));
	y = radius * (float)(sin(headingRadians));
}

void Vector2::SetUnitLengthAndHeadingDegrees(float headingDegrees){
	float radianTheta = ConvertDegreesToRadians(headingDegrees);
	x = (float)(cos(radianTheta));
	y = (float)(sin(radianTheta));
}

void Vector2::SetUnitLengthAndHeadingRadians(float headingRadians){
	x = (float)(cos(headingRadians));
	y = (float)(sin(headingRadians));
}

void Vector2::SetLengthAndHeadingDegrees(float newLength, float headingDegrees){
	float radianTheta = ConvertDegreesToRadians(headingDegrees);
	x = (float)(newLength * cos(radianTheta));
	y = (float)(newLength * sin(radianTheta));
}

void Vector2::SetLengthAndHeadingRadians(float newLength, float headingRadians){
	x = (float)(newLength * cos(headingRadians));
	y = (float)(newLength * sin(headingRadians)); 
}





Vector2 Interpolate(const Vector2& start, const Vector2& end, float fractionToEnd) {
	float fractionOfStart = 1.f - fractionToEnd;
	Vector2 blended;
	blended = (fractionOfStart * start) + (fractionToEnd * end);
	return blended;
}

//-------Operator Overloaders---------------

void Vector2::operator-=(const Vector2& vectorToSubtract){
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
}

void Vector2::operator+=(const Vector2& vectorToAdd){
	x += vectorToAdd.x;
	y += vectorToAdd.y;
}

void Vector2::operator*=(const Vector2& perAxisScaleFactors){
	x *= perAxisScaleFactors.x;
	y *= perAxisScaleFactors.y;
}

void Vector2::operator*=(float scale){
	x *= scale;
	y *= scale;
}

const Vector2 Vector2::operator/(float inverseScale) const{
	
	if (inverseScale == 0) {
		return Vector2(0, 0);
	}
	else {
		float inverse = 1.f / inverseScale;
		return Vector2(inverse*x, inverse*y);
	}
}

const Vector2 Vector2::operator*(const Vector2& perAxisScaleFactors) const{
	return Vector2(perAxisScaleFactors.x*x, perAxisScaleFactors.y*y);
}

const Vector2 Vector2::operator*(float scale) const{
	return Vector2(scale*x, scale*y);
}

const Vector2 Vector2::operator-(const Vector2& vectorToSubtract) const{
	return Vector2(x - vectorToSubtract.x, y - vectorToSubtract.y);
}

const Vector2 Vector2::operator+(const Vector2& vectorToAdd) const{
	return Vector2(x + vectorToAdd.x, y + vectorToAdd.y);
}

bool Vector2::operator!=(const Vector2& vectorToNotEqual) const{
	return (x != vectorToNotEqual.x || y != vectorToNotEqual.y);
}

bool Vector2::operator==(const Vector2& vectorToEqual) const{
	return (x == vectorToEqual.x && y == vectorToEqual.y);
}


//-----------Friend Functions

float DotProduct(const Vector2& a, const Vector2& b){
	return (a.x*b.x) + (a.y*b.y);
}

float CalcDistanceSquared(const Vector2& posA, const Vector2& posB){
	float xDifference = posA.x - posB.x;
	float yDifference = posA.y - posB.y;
	return (xDifference*xDifference) + (yDifference*yDifference);
}

const Vector2 operator * (float scale, const Vector2& vectorToScale) {
	//is this right????
	return Vector2(scale*vectorToScale.x, scale*vectorToScale.y);
}

float CalcDistance(const Vector2& positionA, const Vector2& positionB){
	float xDifference = positionA.x - positionB.x;
	float yDifference = positionA.y - positionB.y;
	return (float) sqrt((xDifference*xDifference) + (yDifference*yDifference));
}


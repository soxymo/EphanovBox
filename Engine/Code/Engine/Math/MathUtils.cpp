#include "Engine/Math/MathUtils.hpp"
#include <stdlib.h>     //for rand
#include <math.h>
#include <time.h>

const float PI = 3.1415926535897932384626f;

float CosDegrees(float degrees) {
	return (float)cos( ConvertDegreesToRadians(degrees) );
}

float SinDegrees(float degrees) {
	return (float)sin(ConvertDegreesToRadians(degrees));
}

float Atan2Degrees(float y, float x) {
	return ConvertRadiansToDegrees( (float)atan2(y, x) );
}

float ConvertRadiansToDegrees(float radians){
	return radians*(180.f / PI);
}

float ConvertDegreesToRadians(float degrees){
	return degrees*(PI / 180.f);
}

int GetRandomIntLessThan(int maxValueNotInclusive){
	return rand() % maxValueNotInclusive;
}

int GetRandomIntInRange(int minValueInclusive, int maxValueInclusive){
	return (rand() % (maxValueInclusive - minValueInclusive)) + minValueInclusive;
}

float GetRandomFloatZeroToOne(){
	//srand((unsigned int)time(NULL));
	return ((float)rand() / (float)RAND_MAX);
}

float GetRandomFloatInRange(float minimumInclusive, float maximumInclusive){
	float difference = maximumInclusive - minimumInclusive;
	return minimumInclusive + (difference * GetRandomFloatZeroToOne());
}

float RangeMapFloat(float inValue, float inMin, float inMax, float outMin, float outMax) {
	if(inMax==inMin)
		return (outMin + outMax) / 2.f;

	float inRange = inMax - inMin;
	float scale = (inValue-inMin) / inRange; //normalized here
	return (scale*(outMax - outMin)) + outMin;
}

float CalcDistanceBetweenAnglesDegrees(float startDegrees, float endDegrees) {
	float angularDist = endDegrees - startDegrees;
	while (angularDist > 180.f)
		angularDist -= 360.f;
	while (angularDist < -180.f)
		angularDist += 360;
	return angularDist;
}

float FastFloor(float val) {
	return (float)floor(val);
}

float SmoothStep(float inputZeroToOne) {
	return 3 * (inputZeroToOne*inputZeroToOne) - 2 * (inputZeroToOne*inputZeroToOne*inputZeroToOne);
}

float SmoothStep5(float inputZeroToOne) {
	float product = 0;
	product += 6 * (inputZeroToOne*inputZeroToOne*inputZeroToOne*inputZeroToOne*inputZeroToOne);
	product -= 15 * (inputZeroToOne*inputZeroToOne*inputZeroToOne*inputZeroToOne);
	product += 10 * (inputZeroToOne*inputZeroToOne*inputZeroToOne);
	return product;
}

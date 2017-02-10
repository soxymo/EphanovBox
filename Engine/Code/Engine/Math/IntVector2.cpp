#include "Engine/Math/IntVector2.hpp"


IntVector2::IntVector2(int initialX, int initialY) {
	x = initialX;
	y = initialY;
}

IntVector2::IntVector2(const IntVector2& copy) {
	x = copy.x;
	y = copy.y;
}

void IntVector2::SetXY(int newX, int newY) {
	x = newX;
	y = newY;
}



void IntVector2::operator-=(const IntVector2& vectorToSubtract) {
	x -= vectorToSubtract.x;
	y -= vectorToSubtract.y;
}

void IntVector2::operator+=(const IntVector2& vectorToAdd) {
	x += vectorToAdd.x;
	y += vectorToAdd.y;
}

const IntVector2 IntVector2::operator-(const IntVector2& vectorToSubtract) const {
	return IntVector2(x - vectorToSubtract.x, y - vectorToSubtract.y);
}

const IntVector2 IntVector2::operator+(const IntVector2& vectorToAdd) const {
	return IntVector2(x + vectorToAdd.x, y + vectorToAdd.y);
}

bool operator < (const IntVector2& lhs, const IntVector2& rhs){
	if (lhs.y < rhs.y)
		return true;
	if (lhs.y > rhs.y)
		return false;
	return lhs.x < rhs.x;
}

bool operator > (const IntVector2& lhs, const IntVector2& rhs){
	if (lhs.y > rhs.y)
		return true;
	if (lhs.y < rhs.y)
		return false;
	return lhs.x > rhs.x;
}

bool operator != (const IntVector2& lhs, const IntVector2& rhs) {
	if (lhs.y != rhs.y || lhs.x != rhs.x)
		return false;
	return true;
}


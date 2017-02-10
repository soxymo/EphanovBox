#include "Engine/Math/IntVector3.hpp"


IntVector3::IntVector3(int initialX, int initialY, int initialZ) {
	x = initialX;
	y = initialY;
	z = initialZ;
}

IntVector3::IntVector3(const IntVector3& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

void IntVector3::SetXYZ(int newX, int newY, int newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

const IntVector3 IntVector3::operator-(const IntVector3& vectorToSubtract) const {
	return IntVector3(x - vectorToSubtract.x, y - vectorToSubtract.y, z - vectorToSubtract.z);
}

const IntVector3 IntVector3::operator+(const IntVector3& vectorToAdd) const {
	return IntVector3(x + vectorToAdd.x, y + vectorToAdd.y, z + vectorToAdd.z);
}


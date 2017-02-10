#pragma once


class IntVector3 {
public:
	int x;
	int y;
	int z;

	IntVector3() {};
	IntVector3(int initialX, int initialY, int initialZ);
	IntVector3(const IntVector3& copy);

	void SetXYZ(int newX, int newY, int newZ);
	const IntVector3 operator + (const IntVector3& vectorToAdd) const;
	const IntVector3 operator - (const IntVector3& vectorToSubtract) const;
};
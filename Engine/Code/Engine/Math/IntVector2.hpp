#pragma once


class IntVector2 {

public:
	int x;
	int y;

	IntVector2() {};
	explicit IntVector2(int initialX, int initialY);
	IntVector2(const IntVector2& copy);
	void SetXY(int newX, int newY);
	const IntVector2 operator + (const IntVector2& vectorToAdd) const;
	const IntVector2 operator - (const IntVector2& vectorToSubtract) const;
	void operator +=(const IntVector2& vectorToAdd);
	void operator -=(const IntVector2& vectorToSubtract);
	
	friend bool operator < (const IntVector2& lhs, const IntVector2& rhs);
	friend bool operator > (const IntVector2& lhs, const IntVector2& rhs);
	friend bool operator != (const IntVector2& lhs, const IntVector2& rhs);

};
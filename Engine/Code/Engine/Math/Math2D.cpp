#include "Math2D.hpp"

bool DoAABBsOverlap(const AABB2& first, const AABB2& second) {
	if (first.max.x < second.min.x)
		return false;
	if (first.max.y < second.min.y)
		return false;
	if (first.min.x > second.max.x)
		return false;
	if (first.min.y > second.max.y)
		return false;
	
	return true;
}

bool DoDiscsOverlap(const Disc2& first, const Disc2& second) {
	float totalRadius = first.radius + second.radius;
	if (CalcDistanceSquared(first.center, second.center) > totalRadius*totalRadius)
		return false;
	else
		return true;
}

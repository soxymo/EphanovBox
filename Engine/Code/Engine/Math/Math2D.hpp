#pragma once
#include "AABB2.hpp"
#include "Disc2.hpp"
#include "Vector2.hpp"

bool DoAABBsOverlap(const AABB2& first, const AABB2& second);
bool DoDiscsOverlap(const Disc2& first, const Disc2& second);

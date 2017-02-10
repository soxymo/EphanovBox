#pragma once
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Rgba.hpp"


class Vertex3 {
public:
	Vector3 m_pos;
	Rgba m_tint;
	Vector2 m_texCoords;

	Vertex3();
	Vertex3(Vector3 pos, Vector2 texCoords, Rgba tint);
	Vertex3(const Vertex3& copy);

	void SetPositionAndTexelCoords(const Vector3& newPos, const Vector2& newTexelCoords);
	

};
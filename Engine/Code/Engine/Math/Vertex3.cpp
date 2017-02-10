#include "Engine/Math/Vertex3.hpp"


Vertex3::Vertex3()
	:m_pos(0.f,0.f,0.f)
	,m_texCoords(0.f,0.f)
	,m_tint()
{
}

Vertex3::Vertex3(Vector3 pos, Vector2 texCoords, Rgba tint) {
	m_pos = pos;
	m_texCoords = texCoords;
	m_tint = tint;
}

Vertex3::Vertex3(const Vertex3& copy) {
	m_pos = copy.m_pos;
	m_texCoords = copy.m_texCoords;
	m_tint = copy.m_tint;
}



void Vertex3::SetPositionAndTexelCoords(const Vector3& newPos, const Vector2& newTexelCoords) {
	m_pos = newPos;
	m_texCoords = newTexelCoords;
}


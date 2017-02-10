#pragma once
#include "Engine/RHI/DX11.hpp"
#include "Engine/Math/Vertex3.hpp"

typedef unsigned int uint;

class RHIDevice;

class VertexBuffer
{
public:
	VertexBuffer(RHIDevice* owner,
		Vertex3 const* vertices,
		uint const vertex_count,
		eBufferUsage usage = BUFFERUSAGE_STATIC);
	~VertexBuffer();

	inline bool is_valid() const { return (dx_buffer != nullptr); }

public:
	ID3D11Buffer* dx_buffer;
};
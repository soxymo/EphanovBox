#pragma once

#include "Engine/RHI/RHITypes.hpp"
#include "Engine/RHI/DX11.hpp"
class RHIDevice;
class RHIDeviceContext;

class ConstantBuffer {
public:
	ConstantBuffer(RHIDevice* owner, void const* buffer, size_t const buffer_size);
	~ConstantBuffer();

	bool update(RHIDeviceContext* context, const void* buffer);

public:
	ID3D11Buffer* dx_buffer;
	size_t buffer_size;
};
#pragma once
#include "Engine/RHI/DX11.hpp"
#include "Engine/RHI/DX11.hpp"
class RHIDevice;

class RasterState {
public:
	RasterState(RHIDevice* owner);
	~RasterState();
	inline bool is_valid() const { return (nullptr != dx_state); }

public:
	RHIDevice *device;
	ID3D11RasterizerState *dx_state;

	
};



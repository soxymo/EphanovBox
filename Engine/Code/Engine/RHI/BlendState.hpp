#pragma once
#include "Engine/RHI/DX11.hpp"


enum eBlendFactor {
	BLEND_ONE,
	BLEND_ZERO,

	BLEND_SRC_ALPHA,
	BLEND_INV_SRC_ALPHA,

	BLEND_SRC_COLOR,
	BLEND_DEST_COLOR,
};


class RHIDevice;

class BlendState {
public:
	BlendState(RHIDevice* owner, bool isEnabled, eBlendFactor const src_factor, eBlendFactor dest_factor);
	~BlendState();
	inline bool is_valid() const { return (nullptr != dx_state); }

public:
	RHIDevice *device;
	ID3D11BlendState *dx_state;
	bool enabled;
};



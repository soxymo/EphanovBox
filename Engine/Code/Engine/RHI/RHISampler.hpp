#pragma once
#include "Engine/RHI/RHITypes.hpp"
#include "Engine/RHI/DX11.hpp"

class RHIDevice;

enum eFilterMode {
	FILTER_POINT,
	FILTER_LINEAR
};


class RHISampler {
public:
	RHISampler(RHIDevice* owner);
	~RHISampler();

	bool create_sampler(eFilterMode min_filter, eFilterMode mag_filter);


public:
	RHIDevice* device;
	ID3D11SamplerState* dx_sampler;
};
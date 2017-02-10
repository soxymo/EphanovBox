#include "Engine/RHI/RHISampler.hpp"
#include "Engine/RHI/RHIDevice.hpp"

//fun memset stuff
template <typename T>
inline void MemZero(T* ptr) {
	memset(ptr, 0, sizeof(T));
}

RHISampler::RHISampler(RHIDevice* owner)
	:device(owner)
	,dx_sampler(nullptr)
{
}

static D3D11_FILTER DXGetFilterMode(eFilterMode min, eFilterMode mag) {
	if (min == FILTER_POINT) {
		if (mag == FILTER_POINT) {
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		}
		else {
			return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		}
	}
	else {
		if (mag == FILTER_POINT) {
			return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		}
		else {
			return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		}
	}
}

bool RHISampler::create_sampler(eFilterMode min_filter, eFilterMode mag_filter) {
	D3D11_SAMPLER_DESC desc;
	MemZero(&desc); 
	desc.Filter = DXGetFilterMode(min_filter, mag_filter);
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//desc.BorderColor = 0; //BLACK TRANSPARENT
	desc.MinLOD = 0;
	desc.MinLOD = 0;

	ID3D11Device* dex_device = device->dx_device;
	HRESULT hr = dex_device->CreateSamplerState(&desc, &dx_sampler);

	return SUCCEEDED(hr);
}

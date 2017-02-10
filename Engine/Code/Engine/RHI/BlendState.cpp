#include "Engine/RHI/BlendState.hpp"
#include "Engine/RHI/RHIDevice.hpp"

static D3D11_BLEND ToDXFactor(eBlendFactor const factor) {
	switch (factor) {
	case BLEND_ONE:
		return D3D11_BLEND_ONE;

	case BLEND_ZERO:
		return D3D11_BLEND_ZERO;

	case BLEND_SRC_ALPHA:
		return D3D11_BLEND_SRC_ALPHA;

	case BLEND_INV_SRC_ALPHA:
		return D3D11_BLEND_INV_SRC_ALPHA;

	default:
		return D3D11_BLEND_ONE;
	}
}

template <typename T>
inline void MemZero(T* ptr) {
	memset(ptr, 0, sizeof(T));
}


BlendState::BlendState(RHIDevice* owner, bool isEnabled, eBlendFactor const src_factor, eBlendFactor dest_factor) :device(owner)
	,dx_state(nullptr)
	,enabled(false)
{
	D3D11_BLEND_DESC desc;
	MemZero(&desc);

	enabled = isEnabled;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = enabled;;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;;
	desc.RenderTarget[0].SrcBlend = ToDXFactor(src_factor);
	desc.RenderTarget[0].DestBlend = ToDXFactor(dest_factor);

	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11Device* dx_device = device->dx_device;
	dx_device->CreateBlendState(&desc, &dx_state);
	

	
}


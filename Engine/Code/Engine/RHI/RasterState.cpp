#include "Engine/RHI/RasterState.hpp"
#include "Engine/RHI/RHIDevice.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"

template <typename T>
inline void MemZero(T* ptr) {
	memset(ptr, 0, sizeof(T));
}


RasterState::RasterState(RHIDevice* owner) 
	:device(owner)
	,dx_state(nullptr)
{
	D3D11_RASTERIZER_DESC desc;
	MemZero(&desc);

	desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME
	desc.CullMode = D3D11_CULL_BACK;

	//make it act like OpenGL
	desc.FrontCounterClockwise = true;
	desc.AntialiasedLineEnable = false;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.SlopeScaledDepthBias = 0.0f;
	desc.ScissorEnable = false;
	desc.MultisampleEnable = false;

	HRESULT hr = device->dx_device->CreateRasterizerState(&desc, &dx_state);
	if (FAILED(hr)) {
		DebuggerPrintf("Raster State could not be created");
	}
}

#include "Engine/RHI/RHIDevice.hpp"
#include "Engine/RHI/RHIDeviceContext.hpp"
#include "Engine/RHI/VertexBuffer.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/RHI/ShaderProgram.hpp"
#include "Engine/RHI/Texture2D.hpp"
#include "Engine/RHI/Image.hpp"

//ShaderProgram* RHIDevice::create_shader_from_hlsl_file(char const *filename) {
//	
//	std::vector< unsigned char > buffer;
//	bool success = LoadBinaryFileToBuffer("data/hlsl/nop_color.hlsl", buffer);
//
//	return nullptr;
//}

RHIDeviceContext* RHIDevice::get_immediate_context() {
	//D3D fun
	ID3D11DeviceContext* dx_context;
	DWORD createDeviceFlags = 0;
	D3D_FEATURE_LEVEL fl;
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, createDeviceFlags, nullptr,
		0, D3D11_SDK_VERSION, &dx_device, &fl, &dx_context);
	if (FAILED(hr)) {
		DebuggerPrintf("Unable to create immediate context in RHIDevice");
	}

	immediate_context = new RHIDeviceContext(this, dx_context);
	return immediate_context;
}

ShaderProgram* RHIDevice::create_shader_from_hlsl_file(char const* filename) {
	return new ShaderProgram(this, filename);
}

VertexBuffer* RHIDevice::create_vertex_buffer(Vertex3 const* vertices, unsigned int const vertex_count, eBufferUsage const usage /*= BUFFERUSAGE_STATIC*/) {
	return new VertexBuffer(this, vertices, vertex_count, usage);
}

Texture2D* RHIDevice::create_texture2D_from_file(char const *filename) {
	
	return new Texture2D(this, filename);
	
}

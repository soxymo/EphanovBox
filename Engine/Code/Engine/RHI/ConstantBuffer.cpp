#include "Engine/RHI/ConstantBuffer.hpp"
#include "Engine/RHi/RHIDevice.hpp"
#include "Engine/RHi/RHIDeviceContext.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"



ConstantBuffer::ConstantBuffer(RHIDevice* owner, void const* buffer, size_t const buffer_size) {
	D3D11_BUFFER_DESC vb_desc;
	memset(&vb_desc, 0, sizeof(vb_desc));

	this->buffer_size = buffer_size;

	vb_desc.ByteWidth = (uint)buffer_size;
	vb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vb_desc.Usage = D3D11_USAGE_DYNAMIC;

	vb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vb_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initial_data;
	memset(&initial_data, 0, sizeof(initial_data));
	initial_data.pSysMem = buffer;

	dx_buffer = nullptr;
	HRESULT hr= owner->dx_device->CreateBuffer(&vb_desc, &initial_data, &dx_buffer);
	if (FAILED(hr)) {
		DebuggerPrintf("Constant Buffer could not be created");
	}
}

bool ConstantBuffer::update(RHIDeviceContext* context, const void* buffer) {
		D3D11_MAPPED_SUBRESOURCE resource;
		ID3D11DeviceContext* dx_context = context->dx_context;
	
		//D3D11_MAP_WRITE_DISCARD writes to whole new buffer
		if (SUCCEEDED(dx_context->Map(dx_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0U, &resource)) ){
			memcpy(resource.pData, buffer, buffer_size);
			dx_context->Unmap(dx_buffer, 0);
			return true;
		}
	
		//TODO ASSERT?
		return false;
}

//bool ConstantBuffer::update(RHIDeviceContext* context, const void* buffer) {
//	D3D11_MAPPED_SUBRESOURCE resource;
//	ID3D11DeviceContext* dx_context = context->dx_context;
//
//	//D3D11_MAP_WRITE_DISCARD writes to whole new buffer
//	if (SUCCEEDED(dx_context->Map(dx_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0U, &resource)) ){
//		memcpy(resource.pData, buffer, buffer_size);
//		dx_context->Unmap(dx_buffer, 0);
//		return true;
//	}
//
//	//TODO ASSERT?
//	return false;
//}

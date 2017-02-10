#include "Engine/RHi/VertexBuffer.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/RHi/RHIDevice.hpp"


VertexBuffer::VertexBuffer(RHIDevice* owner, Vertex3 const* vertices, uint const vertex_count, eBufferUsage usage /*= BUFFERUSAGE_STATIC*/) {
	UNREFERENCED_PARAMETER(usage); //TODO actually use this
	D3D11_BUFFER_DESC vb_desc;
	memset(&vb_desc, 0, sizeof(vb_desc));

	vb_desc.ByteWidth = sizeof(Vertex3) * vertex_count;  // How much data are we putting into this buffer
	vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;         // What can we bind this data as (in this case, only vertex data)
	vb_desc.Usage = D3D11_USAGE_IMMUTABLE;                // Hint on how this memory is used (in this case, it is immutable, or constant - can't be changed)
														  // for limitations/strenghts of each, see;  
														  //    https://msdn.microsoft.com/en-us/library/windows/desktop/ff476259(v=vs.85).aspx
	vb_desc.StructureByteStride = sizeof(Vertex3);       // How large is each element in this buffer

														  // Next, setup the initial data (required since this is an immutable buffer - so it must be instantiated at creation time)
	D3D11_SUBRESOURCE_DATA initial_data;
	memset(&initial_data, 0, sizeof(initial_data));
	initial_data.pSysMem = vertices;

	// Finally create the vertex buffer
	HRESULT hr = owner->dx_device->CreateBuffer(&vb_desc, &initial_data, &dx_buffer);
	if (FAILED(hr)) {
		DebuggerPrintf("VertexBuffer cannot be created");
	}
}


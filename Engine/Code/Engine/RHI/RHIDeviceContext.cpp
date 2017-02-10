#include "Engine/RHI/RHIDeviceContext.hpp"
#include "Engine/RHI/VertexBuffer.hpp"
#include "Engine/RHI/ShaderProgram.hpp"
#include "Engine/RHI/RasterState.hpp"
#include "Engine/RHI/BlendState.hpp"




RHIDeviceContext::RHIDeviceContext(RHIDevice *owner, ID3D11DeviceContext *ctx) {
	device = owner;
	dx_context = ctx;
}


void RHIDeviceContext::clear_color_target(const Texture2D* output, Rgba const &color) {
	float r, g, b, a;
	color.GetAsFloats(r, g, b, a);
	float clear_color[4] = {r, g, b, a};
	dx_context->ClearRenderTargetView(output->dx_rtv, clear_color);
}

void RHIDeviceContext::set_color_target(Texture2D *target) {
	dx_context->OMSetRenderTargets(1, &target->dx_rtv, nullptr);
}

void RHIDeviceContext::set_viewport(uint x, uint y, uint width, uint height) {
	D3D11_VIEWPORT viewport;
	memset(&viewport, 0, sizeof(viewport));
	viewport.TopLeftX = (FLOAT)x; //TODO complier throws warning cause it think it on D3D10
	viewport.TopLeftY = (FLOAT)y;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;        // must be between 0 and 1 (defualt is 0);
	viewport.MaxDepth = 1.0f;        // must be between 0 and 1 (default is 1)
	dx_context->RSSetViewports(1, &viewport);
}

void RHIDeviceContext::set_shader_program(ShaderProgram *shader) {
	dx_context->VSSetShader(shader->dx_vertex_shader, nullptr, 0U);
	dx_context->PSSetShader(shader->dx_fragment_shader, nullptr, 0U);
	dx_context->IASetInputLayout(shader->dx_input_layout); //TODO setInputLayout is questionable

}


void RHIDeviceContext::setRasterState(RasterState* raster) {
	dx_context->RSSetState(raster->dx_state);
}

void RHIDeviceContext::SetBlendState(BlendState* bs) {
	float constant[] = { 1,1,1,1 };
	dx_context->OMSetBlendState(bs->dx_state, constant, 0xffffffff);
}

void RHIDeviceContext::draw(ePrimitiveType const topology, VertexBuffer *vbo, uint const vertex_count, uint const start_idx /*= 0U*/) {
	UNREFERENCED_PARAMETER(start_idx);
	UNREFERENCED_PARAMETER(topology); //TODO get on this
	uint stride = sizeof(Vertex3);
	uint offset = 0U;
	dx_context->IASetVertexBuffers(0,    // Start slot index
		1,                      // Number of buffers we're binding
		&vbo->dx_buffer,      // Array of buffers
		&stride,                // Stride (read: vertex size, or amount we move forward each vertex) for each buffer
		&offset);

	dx_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dx_context->Draw(vertex_count, 0); //TODO update number here
}


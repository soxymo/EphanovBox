#pragma once

#include "Engine/Core/Rgba.hpp"
#include "Engine/RHI/Texture2D.hpp"

typedef unsigned int uint;

class ShaderProgram;
class VertexBuffer;
class RasterState;
class BlendState;

class RHIDeviceContext
{
public:
	RHIDeviceContext(RHIDevice *owner, ID3D11DeviceContext *ctx);
	~RHIDeviceContext();

	// For an immediate/display context, we need the window we're rendering to
	// and the swapchain that manages the render target
	void clear_state();  // clears all rendering state
	void flush();        // flushes all commands


	void clear_color_target(const Texture2D* output, Rgba const &color);

	void set_color_target(Texture2D *target);

	void set_viewport(uint x, uint y, uint width, uint height);
	void set_shader_program(ShaderProgram *shader);

	void set_texture(uint const idx, Texture2D *texture);

	void setRasterState(RasterState* raster);

	void SetBlendState(BlendState* bs);

	void draw(ePrimitiveType const topology,
		VertexBuffer *vbo,
		uint const vertex_count,
		uint const start_idx = 0U);

public:
	RHIDevice *device;
	ID3D11DeviceContext *dx_context;
};
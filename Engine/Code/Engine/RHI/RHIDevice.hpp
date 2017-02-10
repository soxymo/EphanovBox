#pragma once


#include "Engine/RHI/RHITypes.hpp"
#include "Engine/RHI/DX11.hpp"
#include "Engine/Core/Window.hpp"
//#include "Engine/RHI/ShaderProgram.hpp"
// Include all RHIClasses
// <none for now>

// Forward declare the context since I know about it
// but don't need to use it (whereas RHIDeviceContext needs to 
// use device)
class RHIDeviceContext;
class RHIOutput;
class Vertex3;
class VertexBuffer; //TODO could cause problems, delete if don't
class ShaderProgram;
class Texture2D;

// Created from RenderInstance when initial output is created
class RHIDevice
{
public:
	RHIDevice() {}
	~RHIDevice();

	RHIDeviceContext* get_immediate_context();

	// [OPTIONAL] Ability to create secondary outputs
	//            Neat for screensavers, tools, or utlizing a second monitor
	//RHIOutput* create_output(Window *window, eRHIOutputMode const mode);
	//RHIOutput* create_output(unsigned int const px_width, unsigned int const px_height, eRHIOutputMode const mode);

	ShaderProgram* create_shader_from_hlsl_file(char const* filename);

	VertexBuffer* create_vertex_buffer(Vertex3 const* vertices,
		unsigned int const vertex_count,
		eBufferUsage const usage = BUFFERUSAGE_STATIC);

	Texture2D* create_texture2D_from_file(char const *filename);

	//TODO do this eventually
	/*IndexBuffer* create_vertex_buffer(uint32_t const *indices
		uint const index_count,
		eBufferUsage const usage = BUFFERUSAGE_STATIC);*/


public:
	// Immediate Mode Context - Created with the Device
	RHIDeviceContext *immediate_context;
	ID3D11Device *dx_device;
};
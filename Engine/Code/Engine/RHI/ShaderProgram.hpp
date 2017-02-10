#pragma once
#include "Engine/RHI/DX11.hpp"

class RHIDevice;

typedef unsigned int uint;

enum eShaderStage
{
	SHADER_VERTEX,    // maps to target "vs_5_0", or Vertex Shader Model 5 (currently latest)
	SHADER_FRAGMENT,  // maps to target "ps_5_0", or Pixel Shader Model 5 (currently latest)
};


class ShaderProgram {

public:
	ShaderProgram(RHIDevice *owner, char const* filename);
	~ShaderProgram();

	void set_shader(ShaderProgram* program);

	inline bool is_valid() const { return (dx_vertex_shader != nullptr) && (dx_fragment_shader != nullptr); }

private:
	void create_input_layout(RHIDevice* device);
	void create_shaders(RHIDevice* device, const char* filename);

public:
	// All the steps to this (could be split out to a ShaderStage)
	ID3D11VertexShader *dx_vertex_shader;
	ID3D11PixelShader *dx_fragment_shader;

	// Input Layout - for now, we're going 
	// to assume every shader makes their own
	// for simplicity, but honestly you should make these
	// based on need
	ID3D11InputLayout *dx_input_layout;

	// [OPTIONAL] ByteCode - only need to keep it around if using Reflection
	ID3DBlob *vs_byte_code;
	ID3DBlob *fs_byte_code;
};
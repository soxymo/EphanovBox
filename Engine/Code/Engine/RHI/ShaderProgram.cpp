#include "Engine/RHI/ShaderProgram.hpp"
#include "Engine/RHI/RHIDevice.hpp"
#include "Engine/Math/Vertex3.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"

#include <d3dcompiler.h>
#pragma comment( lib, "d3dcompiler.lib" )

#define DX_SAFE_RELEASE(dx_resource)   if ((dx_resource) != nullptr) { dx_resource->Release(); dx_resource = nullptr; }
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

//I love PI
ShaderProgram::ShaderProgram(RHIDevice *owner, char const* filename) {
	create_shaders(owner, filename);
	create_input_layout(owner);
	

	//owner->dx_device->VSSetShader(dx_vertex_shader, nullptr, 0U);  //TODO gotta set the shader somewhere, why not here?
	//gD3DContext->PSSetShader(gD3DFragmentShader, nullptr, 0U);
	//DX_SAFE_RELEASE(vs_byte_code);
	//DX_SAFE_RELEASE(fs_byte_code);
}

ShaderProgram::~ShaderProgram() {
	
}

void ShaderProgram::set_shader(ShaderProgram* program) {
	//gD3DContext->VSSetShader(gD3DVertexShader, nullptr, 0U);
	//gD3DContext->PSSetShader(gD3DFragmentShader, nullptr, 0U);
	dx_vertex_shader = program->dx_vertex_shader;
	dx_fragment_shader = program->dx_fragment_shader;
	dx_input_layout = program->dx_input_layout;
}

void ShaderProgram::create_input_layout(RHIDevice* device) {
	D3D11_INPUT_ELEMENT_DESC DESC[3];
	memset(DESC, 0, sizeof(DESC));
	DESC[0].SemanticName = "POSITION";
	DESC[0].SemanticIndex = 0;
	DESC[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;//DXGI_FORMAT_R32G32B32_FLOAT;
	DESC[0].InputSlot = 0U;
	DESC[0].AlignedByteOffset = offsetof(Vertex3, m_pos);
	DESC[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	DESC[0].InstanceDataStepRate = 0U;

	DESC[1].SemanticName = "COLOR";
	DESC[1].SemanticIndex = 0;
	DESC[1].Format = DXGI_FORMAT_R8G8B8A8_UINT;//DXGI_FORMAT_R32G32B32_FLOAT;
	DESC[1].InputSlot = 0U;
	DESC[1].AlignedByteOffset = offsetof(Vertex3, m_tint);
	DESC[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	DESC[1].InstanceDataStepRate = 0U;

	DESC[2].SemanticName = "TEXCOORDS";
	DESC[2].SemanticIndex = 0;
	DESC[2].Format = DXGI_FORMAT_R32G32_FLOAT;//DXGI_FORMAT_R32G32B32_FLOAT;
	DESC[2].InputSlot = 0U;
	DESC[2].AlignedByteOffset = offsetof(Vertex3, m_texCoords);
	DESC[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	DESC[2].InstanceDataStepRate = 0U;


	const void*  bytePointer = vs_byte_code->GetBufferPointer();
	SIZE_T byteLength = vs_byte_code->GetBufferSize();
	UINT arraysize = ARRAYSIZE(DESC);

	

	HRESULT hr	= device->dx_device->CreateInputLayout(DESC, arraysize,
		bytePointer,
		byteLength,
		&dx_input_layout);

	if (FAILED(hr)) {
		DebuggerPrintf("Unable to Create Input Layout");
	}
}



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Helper - File IO Example - Read an entire file to a buffer
// NOTE:  Be sure for free it when you're done.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void* FileReadToBuffer(char const *filename, size_t *out_size) {  //TODO use my fileUtilities instead
	*out_size = 0U;

	// I'm going to use Windows file functions for no particular reason
	// outside of familiarity.  Feel free to use whatever. 
	DWORD file_access = GENERIC_READ;
	DWORD share = FILE_SHARE_READ;
	DWORD options = OPEN_EXISTING;

	HANDLE file_handle = CreateFileA(filename, file_access, share, NULL, options, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_handle == INVALID_HANDLE_VALUE) {
		DebuggerPrintf("File [%s] could not be opened.", filename);
		return nullptr;
	}

	// Get File Size
	DWORD high_word;
	DWORD lo_word = ::GetFileSize(file_handle, &high_word);

	// 64-bit way - use a 64-bit type, but we will never have a 4GB+ file, so ignore it and just using lo-word to prevent warnings
	// size_t size = ((size_t)high_word << 32) | (size_t)lo_word;
	size_t size = (size_t)lo_word;

	// Make a buffer that big
	void *buffer = malloc(size + 1U); // I allocae one extra for a null terminator - but do not include it in the size
									  // just in the cases I load strings it null terminates.
	if (nullptr != buffer) {
		DWORD read = 0U;
		ReadFile(file_handle, buffer, (DWORD)size, &read, nullptr);
		*out_size = read;

		((char*)buffer)[size] = NULL;
	}

	CloseHandle((HANDLE)file_handle);
	return buffer;
}




static ID3DBlob* CompileHLSLToShaderBlob(char const *opt_filename,  // optional: used for error messages
	void const *source_code,                                          // buffer containing source code.
	size_t const source_code_size,                                    // size of the above buffer.
	char const *entrypoint,                                           // Name of the Function we treat as the entry point for this stage
	char const* target)                                             // What stage we're compiling for (Vertex/Fragment/Hull/Compute... etc...)
{
	/* DEFINE MACROS - CONTROLS SHADER
	// You can optionally define macros to control compilation (for instance, DEBUG builds, disabling lighting, etc...)
	D3D_SHADER_MACRO defines[1];
	defines[0].Name = "TEST_MACRO";
	defines[0].Definition = nullptr;
	*/

	DWORD compile_flags = 0U;
#if defined(DEBUG_SHADERS)
	compile_flags |= D3DCOMPILE_DEBUG;
	compile_flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
	compile_flags |= D3DCOMPILE_WARNINGS_ARE_ERRORS;   // cause, FIX YOUR WARNINGS
else 
	// compile_flags |= D3DCOMPILE_SKIP_VALIDATION;       // Only do this if you know for a fact this shader works with this device (so second run through of a game)
	compile_flags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;   // Yay, fastness (default is level 1)
#endif

	ID3DBlob *code = nullptr;
	ID3DBlob *errors = nullptr;


	HRESULT hr = D3DCompile(source_code,
		source_code_size,                   // plain text source code
		opt_filename,                       // optional, used for error messages (If you HLSL has includes - it will not use the includes names, it will use this name)
		nullptr,                            // pre-compiler defines - used more for compiling multiple versions of a single shader (different quality specs, or shaders that are mostly the same outside some constants)
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // include rules - this allows #includes in the shader to work relative to the src_file path or my current working directly
		entrypoint,                         // Entry Point for this shader
		target,                             // Compile Target (MSDN - "Specifying Compiler Targets")
		compile_flags,                      // Flags that control compilation
		0,                                  // Effect Flags (we will not be doing Effect Files)
		&code,                              // [OUT] ID3DBlob (buffer) that will store the byte code.
		&errors);                          // [OUT] ID3DBlob (buffer) that will store error information

	if (FAILED(hr) || (errors != nullptr)) {
		if (errors != nullptr) {
			char *error_string = (char*)errors->GetBufferPointer();
			DebuggerPrintf("Failed to compile [%s].  Compiler gave the following output;\n%s",
				opt_filename,
				error_string);
			DX_SAFE_RELEASE(errors);
		}
	}

	// will be nullptr if it failed to compile
	return code;
}




void ShaderProgram::create_shaders(RHIDevice* device, const char* filename) {
	size_t size = 0U;
	void *source_code = FileReadToBuffer(filename, &size);
	if (source_code == nullptr) {
		DebuggerPrintf("--Shader file could not be read. The filename may be wrong.--");
		return;
	}

	// Compile hlsl to byte code (generic compiled version)
	vs_byte_code = CompileHLSLToShaderBlob(filename, source_code, size, "VertexFunction", "vs_5_0");
	fs_byte_code = CompileHLSLToShaderBlob(filename, source_code, size, "FragmentFunction", "ps_5_0");


	HRESULT hr;
	// Compile the byte code to the final shader (driver/hardware specific program)
	hr = device->dx_device->CreateVertexShader(vs_byte_code->GetBufferPointer(),
		vs_byte_code->GetBufferSize(),
		nullptr,
		&dx_vertex_shader);

	if (FAILED(hr)) {
		DebuggerPrintf("It broke yo");
	}

	hr = device->dx_device->CreatePixelShader(fs_byte_code->GetBufferPointer(),
		fs_byte_code->GetBufferSize(),
		nullptr,
		&dx_fragment_shader);
	if (FAILED(hr)) {
		DebuggerPrintf("It broke yo");
	}

}


#pragma once
#include "Engine/Core/Rgba.hpp"
#include "Engine/RHI/RHI.h" //TODO this doesn't seem right, it should be in .cpp, but how!?

#include "Engine/Math/Matrix4.hpp"
#include "Engine/RHI/BlendState.hpp"
#include <string>

class ShaderProgram;
class RHISampler;
class VertexBuffer;
class IndexBuffer;
class RHISampler;
class Texture2D;
class RasterState;
class ConstantBuffer;
class Font;

typedef unsigned int uint;




struct matrix_buffer_t {
	Matrix4 model;
	Matrix4 view;
	Matrix4 projection;
};

struct time_buffer_t {
	float game_time;
	Vector3 padding;
};

struct input_buffer_t {
	float zoom;
	Vector3 padding;
};



const int MATRIX_BUFFER_INDEX = 0;
const int TIME_BUFFER_INDEX = 1;
const int INPUT_BUFFER_INDEX = 2;


class SimpleRenderer {
public:
	SimpleRenderer();
	~SimpleRenderer() {};

	// [A02] However you want this to initialize, is up to you
	// For example, all of the following are perfectly good ways to expect
	// this to be used;
	// void setup( RHIOutput *output );
	void setup(uint width, uint height);
	// void setup( Window *window );
	// void setup( Texture2D *default_render_target );

	// Cleanup - could just be the deconstructor.
	void destroy();

	// RENDER TARGETS
	// [A02]
	// Setting nullptr should default to the output. 
	void set_render_target(Texture2D* color_target);

	// [A02]
	void set_viewport(uint x, uint y, uint width, uint height);

	// [A02: Optional]
	// Set the viewport using percentages of the size of the current render target.
	void set_viewport_as_percent(float x, float y, float w, float h);

	// [A02] CLEARING 
	// Clears currently bound target
	void clear_color(Rgba const &color);
	// Clears specified target
	void clear_target_color(Texture2D *target, Rgba const &color);

	// [A02] CLEARING 
	// Calls Outputs Present
	void present();

	// [A02]
	void set_shader(ShaderProgram *shader);

	// [A02]
	void set_texture(uint texture_index, Texture2D *texture);
	inline void set_texture(Texture2D *texture) { set_texture(0, texture); }

	// [A02]
	void set_sampler(uint sampler_index, RHISampler *sampler);
	inline void set_sampler(RHISampler *sampler) { set_sampler(0, sampler); }

	// [A02]
	// Indexed is optional - though highly encouraged to do 
	// during this assignment as it is the easiest assignment to 
	// implement them with
	void draw(ePrimitiveType topology, VertexBuffer *vbo, uint const vertex_count);
	void draw_indexed(ePrimitiveType topology, VertexBuffer *vbo, IndexBuffer *ibo, uint const vertex_count);
	void drawAABB2(const AABB2& square, const Rgba& color);

	void setRasterState(RasterState* rs);

	void setConstantBuffer(unsigned int idx, ConstantBuffer* buffer);

	void set_projection_matrix(Matrix4& mat);
	void set_zoom_input(float zoomLevel);
	void SetOrthoProjection(Vector2& bottomLeft, Vector2& topRight);
	void SetBlendState(BlendState* bs);
	void enable_blend(eBlendFactor src, eBlendFactor dest);
	void disable_blend();
	void DrawText2D(Vector2& pos, float scale, Rgba& color, Font* font, std::string str);

	void DrawAABB3(AABB3 box, Texture2D* texture, CONST Rgba& color);

public:
	// RHI needed stuff
	RHIDeviceContext *context;
	RHIDevice* device;
	RHIOutput* output;
	RasterState* rasterState;

	Texture2D* defaultTexture;

	ConstantBuffer* matrix_cb;
	matrix_buffer_t matrix_data;

	ConstantBuffer* time_cb;
	time_buffer_t time_data;
	
	ConstantBuffer* input_cb;
	input_buffer_t input_data;

	BlendState* current_blend_state;
	

};
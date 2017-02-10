#include "Engine/Renderer/SimpleRenderer.hpp"
#include "Engine/RHI/RHISampler.hpp"
#include "Engine/RHI/RasterState.hpp"
#include "Engine/RHI/ConstantBuffer.hpp"
#include "Engine/RHI/Texture2D.hpp"
#include "Engine/RHI/BlendState.hpp"
#include "Engine/Renderer/Font.h"


SimpleRenderer::SimpleRenderer() : context(nullptr),
device(nullptr),
output(nullptr),
matrix_cb(nullptr),
time_cb(nullptr)
{
}


void SimpleRenderer::setup(uint width, uint height) {
	RHIInstance *ri = &RHIInstance::GetInstance();
	ri->create_output(&context, &output, width, height); //TODO remove height and width?
	device = context->device;

	rasterState = new RasterState(device);
	setRasterState(rasterState);

	defaultTexture = device->create_texture2D_from_file("data/image/default.png");

	input_data.zoom = -10;

	matrix_cb = new ConstantBuffer(device, &matrix_data, sizeof(matrix_data));
	time_cb = new ConstantBuffer(device, &time_data, sizeof(time_data));
	input_cb = new ConstantBuffer(device, &input_data, sizeof(input_data));
	

	//BIND constant buffers
	setConstantBuffer(MATRIX_BUFFER_INDEX, matrix_cb);
	setConstantBuffer(TIME_BUFFER_INDEX, time_cb);
	setConstantBuffer(INPUT_BUFFER_INDEX, input_cb);
}

void SimpleRenderer::set_render_target(Texture2D* color_target) {
	if (color_target == nullptr) { 
		context->set_color_target(output->render_target);
		return;
	}
	context->set_color_target(color_target);
}

void SimpleRenderer::set_viewport(uint x, uint y, uint width, uint height) {
	context->set_viewport(x, y, width, height);
}

void SimpleRenderer::clear_color(Rgba const &color) {
	context->clear_color_target(output->get_render_target(), color);
}

void SimpleRenderer::clear_target_color(Texture2D *target, Rgba const &color) {
	if (target == nullptr) {
		context->clear_color_target(output->get_render_target(), color);
		return;
	}
	context->clear_color_target(target, color);
}

void SimpleRenderer::present() {
	output->present();
}

void SimpleRenderer::set_shader(ShaderProgram *shader) {
	context->set_shader_program(shader);
}

void SimpleRenderer::set_texture(uint texture_index, Texture2D *texture) {
	context->dx_context->VSSetShaderResources(texture_index, 1, &texture->dx_srv);
	context->dx_context->PSSetShaderResources(texture_index, 1, &texture->dx_srv);
}

void SimpleRenderer::set_sampler(uint sampler_index, RHISampler *sampler) {
	context->dx_context->VSSetSamplers(sampler_index, 1, &sampler->dx_sampler);
	context->dx_context->PSSetSamplers(sampler_index, 1, &sampler->dx_sampler);
}

void SimpleRenderer::draw(ePrimitiveType topology, VertexBuffer *vbo, uint const vertex_count) {
	context->draw(topology, vbo, vertex_count);
}


void SimpleRenderer::drawAABB2(const AABB2& sq, const Rgba& color) {
	Vertex3 vertices[] = {
		Vertex3(Vector3(sq.min.x, sq.min.y, 0.0f), Vector2(0.f,1.f), color),
		Vertex3(Vector3(sq.max.x, sq.max.y, 0.0f), Vector2(1.f,0.f), color),
		Vertex3(Vector3(sq.min.x, sq.max.y, 0.0f), Vector2(0.f,0.f), color),
		Vertex3(Vector3(sq.min.x, sq.min.y, 0.0f), Vector2(0.f,1.f), color),
		Vertex3(Vector3(sq.max.x, sq.min.y, 0.0f), Vector2(1.f,1.f), color),
		Vertex3(Vector3(sq.max.x, sq.max.y, 0.0f), Vector2(1.f,0.f), color)
	};

	VertexBuffer* temp_vbo = device->create_vertex_buffer(vertices, 6);
	set_texture(defaultTexture);

	draw(PRIMITIVE_TRIANGLES, temp_vbo, 6);
}

void SimpleRenderer::setRasterState(RasterState* rs) {
	context->setRasterState(rs);
}

void SimpleRenderer::setConstantBuffer(unsigned int idx, ConstantBuffer* buffer) {
	context->dx_context->VSSetConstantBuffers(idx, 1, &buffer->dx_buffer); //TODO move to deviceContext
	context->dx_context->PSSetConstantBuffers(idx, 1, &buffer->dx_buffer);
}

void SimpleRenderer::set_projection_matrix(Matrix4& mat) {
	matrix_data.projection = mat.GetTransposed();
	matrix_cb->update(context, &matrix_data);
}


void SimpleRenderer::set_zoom_input(float zoomLevel) {
	input_data.zoom = zoomLevel;
	input_cb->update(context, &input_data);
	setConstantBuffer(INPUT_BUFFER_INDEX, input_cb);
}

void SimpleRenderer::SetOrthoProjection(Vector2& bottomLeft, Vector2& topRight) {
	Matrix4 projection = Matrix4::MatrixMakeOrthoProjection(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, 0.f, 1.f);
	set_projection_matrix(projection);
}

void SimpleRenderer::SetBlendState(BlendState* bs) {
	context->SetBlendState(bs);
}

void SimpleRenderer::enable_blend(eBlendFactor src, eBlendFactor dest) {


	//TODO check if blendmode is exactly the same here

	BlendState* blend_state = new BlendState(device, true, src, dest);
	context->SetBlendState(blend_state);

	blend_state->enabled = true;
	//blend_state->src_factor = src;
	//blend_state->dst_factor = dest;
	current_blend_state = blend_state;

}

void SimpleRenderer::disable_blend() {
	if (!current_blend_state->enabled) {
		return;
	}
	//SAFE_DELETE(current_blend_state);
	//TODO recreate blend state here and disable it.
}

void SimpleRenderer::DrawText2D(Vector2& pos, float scale, Rgba& color, Font* font, const std::string str) {

	UNREFERENCED_PARAMETER(scale);
	Texture2D* fontTexture = device->create_texture2D_from_file(font->textureFilepath);
	set_texture(0, fontTexture);
	Vector2 cursor = pos;

	int lineHeight = font->lineHeight;

	for (unsigned int i = 0; i < str.size(); i++) {
		glyphInfo* glyph = font->GetGlyph(str[i]);

		float topY = cursor.y + lineHeight - glyph->yoffset;
		float bottomY = topY - glyph->height;

		AABB2 sq(cursor + Vector2((float)glyph->xoffset, bottomY), (cursor + Vector2((float)glyph->xoffset, 0.f) + Vector2((float)glyph->width, topY)));

		AABB2 tex(glyph->x / 512.f, glyph->y / 512.f, (glyph->x + glyph->width ) / 512.f, (glyph->y + glyph->height) / 512.f);
		Vertex3 vertices[] = {
			Vertex3(Vector3(sq.min.x, sq.min.y, 0.0f), Vector2(tex.min.x, tex.max.y), color),
			Vertex3(Vector3(sq.max.x, sq.max.y, 0.0f), Vector2(tex.max.x, tex.min.y), color),
			Vertex3(Vector3(sq.min.x, sq.max.y, 0.0f), Vector2(tex.min.x, tex.min.y), color),
			Vertex3(Vector3(sq.min.x, sq.min.y, 0.0f), Vector2(tex.min.x, tex.max.y), color),
			Vertex3(Vector3(sq.max.x, sq.min.y, 0.0f), Vector2(tex.max.x, tex.max.y), color),
			Vertex3(Vector3(sq.max.x, sq.max.y, 0.0f), Vector2(tex.max.x, tex.min.y), color)
		};

		VertexBuffer* temp_vbo = device->create_vertex_buffer(vertices, 6);



		draw(PRIMITIVE_TRIANGLES, temp_vbo, 6);
		cursor.x += glyph->xadvance;
	}

}

/*Vector2 top_left = cursor + Vector2(glyph->xoffset, -glyph->yoffset);
bottom_left = top_left + Vector2(0, -glyph->height);
top_right = top_left + Vector2(glyph->width, 0);
Vector2 bottom_right = bottom_left + Vector2(glyph->width, 0);*/

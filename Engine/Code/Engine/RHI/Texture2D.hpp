#pragma once
#include "Engine/RHI/DX11.hpp"
class RHIDevice; //TODO this might be a mistake
class Image;

class Texture2D
{
public:
	Texture2D(RHIDevice* owner);
	Texture2D(RHIDevice* devicePtr, ID3D11Texture2D* tex);
	Texture2D(RHIDevice* devicePtr, char const* filename);
	~Texture2D();

	unsigned int get_width();
	unsigned int get_height();

	inline bool is_valid() const { return (dx_resource != nullptr); }
	inline bool is_render_target() const { return (dx_rtv != nullptr); }

	bool load_from_image(Image const &img);
	void create_views();

public:
	RHIDevice *device;

	ID3D11Texture2D *dx_resource;
	ID3D11RenderTargetView *dx_rtv;


	unsigned int dx_bind_flags;

	ID3D11ShaderResourceView* dx_srv;

	unsigned int width;
	unsigned int height;
};

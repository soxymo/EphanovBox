#include "Engine/RHI/Texture2D.hpp"
#include "Engine/RHI/RHIDevice.hpp"
#include "Engine/RHI/Image.hpp"


Texture2D::Texture2D(RHIDevice *devicePtr, ID3D11Texture2D *tex) 
	: Texture2D(devicePtr)
{
	dx_resource = tex;

	device->dx_device->CreateRenderTargetView(dx_resource, nullptr, &dx_rtv);

	//TODO ask if I need this
	//DX_SAFE_RELEASE(dx_resource); // I'm done using this - so release my hold on it (does not destroy it!)
}

Texture2D::Texture2D(RHIDevice* devicePtr, char const* filename)
	: Texture2D(devicePtr) 
{
	Image textureImage;
	if (!textureImage.load_from_file(filename)) {
		return;
	}
	load_from_image(textureImage);
}

Texture2D::Texture2D(RHIDevice* owner)
	: device(owner)
	, dx_resource(nullptr)
	, dx_rtv(nullptr)
	, dx_srv(nullptr)
	, width(0)
	, height(0)
	, dx_bind_flags(0U) 
{
}

Texture2D::~Texture2D() {
	// release all resources
}

bool Texture2D::load_from_image(Image const &img) {


	D3D11_USAGE usage = D3D11_USAGE_IMMUTABLE;

	D3D11_TEXTURE2D_DESC tex_desc;
	memset(&tex_desc, 0, sizeof(tex_desc));

	tex_desc.Width = img.get_width();
	tex_desc.Height = img.get_height();
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Usage = usage;
	tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex_desc.CPUAccessFlags = 0U;
	tex_desc.MiscFlags = 0U;

	//multismapling
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	

	dx_bind_flags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = img.buffer;
	data.SysMemPitch = img.bpp * tex_desc.Width;

	dx_resource = nullptr;
	ID3D11Device* dx_device = device->dx_device;
	HRESULT hr = dx_device->CreateTexture2D(&tex_desc, &data, &dx_resource);

	if (SUCCEEDED(hr)) {
		create_views();
		return true;
	}
	else {
		return false;
	}
}

void Texture2D::create_views() {

   ID3D11Device *dd = device->dx_device;
   HRESULT hr;
   if (dx_bind_flags & D3D11_BIND_RENDER_TARGET) {
      hr = dd->CreateRenderTargetView( dx_resource, nullptr, &dx_rtv );
   } 

   if (dx_bind_flags & D3D11_BIND_SHADER_RESOURCE) {
      hr = dd->CreateShaderResourceView( dx_resource, nullptr, &dx_srv );
   }
}


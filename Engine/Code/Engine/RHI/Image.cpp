/************************************************************************/
/*                                                                      */
/* INCLUDE                                                              */
/*                                                                      */
/************************************************************************/
#include "Engine/RHI/Image.hpp"


#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_PNM
#include "ThirdParty/stb/stb_image.h"


Image::~Image() {
	destroy();
}

//------------------------------------------------------------------------
bool Image::load_from_file(char const *filename) {
	destroy();

	int w;
	int h;
	int comp;

	// Force load in with 4 components
	stbi_uc *data = stbi_load(filename, &w, &h, &comp, 0);
	if (data != nullptr) {
		if (comp == 3) {
			stbi_uc *new_buffer = stbi__convert_format(data, comp, 4, w, h);
			// ::free(data);
			data = new_buffer;
		}

		buffer = (byte_t*)data;
		width = w;
		height = h;
		bpp = 4;
		format = IMAGEFORMAT_RGBA8;
		return true;
	}

	return false;
}

//------------------------------------------------------------------------
void Image::destroy() {
	if (nullptr != buffer) {
		::free(buffer);
	}
}

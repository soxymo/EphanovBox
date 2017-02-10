#pragma once
#if !defined( __CORE_IMAGE__ )
#define __GAME_GAME__

/************************************************************************/
/*                                                                      */
/* INCLUDE                                                              */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* DEFINES AND CONSTANTS                                                */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* MACROS                                                               */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* TYPES                                                                */
/*                                                                      */
/************************************************************************/
typedef unsigned int uint;

enum eImageFormat : uint
{
	IMAGEFORMAT_RGBA8, // only supporting this one for class - up to you if you want to support more
};
typedef unsigned __int8      uint8_t;
typedef uint8_t byte_t;

/************************************************************************/
/*                                                                      */
/* STRUCTS                                                              */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* CLASSES                                                              */
/*                                                                      */
/************************************************************************/
class Image
{
public:
	Image()
		: buffer(nullptr)
		, width(0)
		, height(0)
		, bpp(0) {
	}

	~Image();

	bool load_from_file(char const *filename);
	void destroy();

	inline uint get_pixel_size() const { return bpp; }
	inline uint get_width() const { return width; }
	inline uint get_height() const { return height; }
	inline uint get_stride() const { return width * bpp; }
	inline uint get_slice() const { return get_stride() * height; }

public:
	byte_t *buffer;
	uint width;
	uint height;
	uint bpp;

	eImageFormat format;

};
/************************************************************************/
/*                                                                      */
/* GLOBAL VARIABLES                                                     */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* FUNCTION PROTOTYPES                                                  */
/*                                                                      */
/************************************************************************/
#endif 

#pragma once

#include "Engine/RHI/Texture2D.hpp"


class Window;
class RHIDevice;

class RHIOutput
{
public:
	RHIOutput(RHIDevice *owner,
		Window *wnd,
		/*[OPTIONAL]*/ eRHIOutputMode const mode = RENDEROUTPUT_WINDOWED);
	~RHIOutput();

	// Whatever is currently being renderered
	// that is what we're working with.
	void present();
	void close();

	Texture2D* get_render_target();
	float get_width() const;
	float get_height() const;
	float get_aspect_ratio() const;

	// [OPTIONAL]
	bool set_display_mode(eRHIOutputMode const mode,
		float const width = 0.0f,
		float const height = 0.0f);

public:
	RHIDevice *device;
	Window *window;

	IDXGISwapChain *swap_chain;

	Texture2D *render_target;



};
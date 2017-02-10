#pragma once

#include "Engine/RHI/RHIDeviceContext.hpp"
#include "Engine/RHI/RHIOutput.hpp"
#include "Engine/RHI/RHITypes.hpp"
#include "Engine/RHI/RHIDevice.hpp"

class RHIInstance
{
public:
	// Constructor is private:  Singleton Class
	~RHIInstance() {}

	bool RHIInstance::create_output(RHIDeviceContext **out_context,
		RHIOutput **out_output,
		unsigned int const px_width,
		unsigned int const px_height,
		/*OPTIONAL*/ eRHIOutputMode const initial_mode = RENDEROUTPUT_WINDOWED);

private:
	RHIInstance() {}
	

public:
	static RHIInstance& GetInstance();
};
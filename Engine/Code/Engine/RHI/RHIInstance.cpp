#include "Engine/RHI/RHIInstance.hpp"




RHIInstance& RHIInstance::GetInstance()
{
	static RHIInstance staticInstance;
	return staticInstance;
	/*if (!hasInstance) {
		instance = new RHIInstance();
		hasInstance = true;
	}
	return instance;*/
}

bool RHIInstance::create_output(RHIDeviceContext **out_context, RHIOutput **out_output, unsigned int const px_width, unsigned int const px_height, /*OPTIONAL*/ eRHIOutputMode const initial_mode /*= RENDEROUTPUT_WINDOWED*/) {
	UNREFERENCED_PARAMETER(initial_mode); //TODO use this param
	UNREFERENCED_PARAMETER(px_width); //TODO use these params to create window
	UNREFERENCED_PARAMETER(px_height);
	RHIDevice* newDevice = new  RHIDevice();
	*out_context = newDevice->get_immediate_context();

	Window* wndPointer = nullptr;
	*out_output = new RHIOutput(newDevice, wndPointer);
	return true; //TOOD make return bool mean something
}


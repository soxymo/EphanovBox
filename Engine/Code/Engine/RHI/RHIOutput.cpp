#include "Engine/RHI/RHIOutput.hpp"
#include "Engine/Core/Config.hpp"
#include "Engine/RHI/DX11.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/RHI/RHIDevice.hpp"

RHIOutput::RHIOutput(RHIDevice *owner, Window *wnd, /*[OPTIONAL]*/ eRHIOutputMode const mode /*= RENDEROUTPUT_WINDOWED*/) {
	UNREFERENCED_PARAMETER(mode); //TODO do something with this
	device = owner;
	
	Config testConfig;
	testConfig.ConfigSystemStartup("config.txt");

	int winWidth;
	if (!testConfig.ConfigGetInt(&winWidth, "windowWidth")) {
		winWidth = 1600;
	}

	int winHeight;  //TODO currently does nothing!!!!!
	if (!testConfig.ConfigGetInt(&winHeight, "windowHeight")) {
		winHeight = 900;
	}

	int winPhysWidth;
	if (!testConfig.ConfigGetInt(&winPhysWidth, "windowPhysicalWidth")) {
		winPhysWidth = 800;
	}

	int winPhysHeight;
	if (!testConfig.ConfigGetInt(&winPhysHeight, "windowPhysicalheight")) {
		winPhysHeight = 450;
	}

	window = new Window();
	window->RegisterGameWindowClass();
	HWND windowHandle = window->CreateTheWindow("D3D super test collider test", winPhysWidth, winPhysHeight, winWidth, winHeight);
	window->Open();

	wnd = window;

	//Setup Swap Chain
	DXGI_SWAP_CHAIN_DESC swap_desc;
	memset(&swap_desc, 0, sizeof(swap_desc));

	// fill the swap chain description struct
	swap_desc.BufferCount = 2;                                    // two buffers (one front, one back?)

	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT       // how swap chain is to be used
		| DXGI_USAGE_BACK_BUFFER;
	swap_desc.OutputWindow = windowHandle;                                // the window to be copied to on present
	swap_desc.SampleDesc.Count = 1;                               // how many multisamples (1 means no multi sampling)

																  // Default options.
	swap_desc.Windowed = TRUE;                                    // windowed/full-screen mode
	swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swap_desc.BufferDesc.Width = winWidth;
	swap_desc.BufferDesc.Height = winHeight;


	//The long process of getting a swap chain
	//TODO make hr mean something
	HRESULT hr;
	IDXGIDevice* DXGIDevice = nullptr;
	hr = device->dx_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* adapter = nullptr;
	hr = DXGIDevice->GetAdapter(&adapter);

	IDXGIFactory* factory = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);

	hr = factory->CreateSwapChain(
		owner->dx_device,
		&swap_desc,
		&swap_chain
		);


	ID3D11Texture2D* texturePointer = nullptr;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texturePointer);
	render_target = new Texture2D(device, texturePointer);
}

void RHIOutput::present() {
	swap_chain->Present(0,0);
}

Texture2D* RHIOutput::get_render_target() {
	return render_target;
}


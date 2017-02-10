//#define WIN32_LEAN_AND_MEAN
#include "Engine/Core/Window.hpp"
//#include <windows.h>
//#include <gl/gl.h>
//#include <math.h>
//#include <cassert>
//#include <crtdbg.h>
//#include <string>
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/StringUtils.hpp"
#include "Engine/Core/Config.hpp"


#define WNDCLASS_GAME_NAME    (L"GameWindowClass")
#define WNDCLASS_GAME_NAME_LPCSTR    ("GameWindowClass")



Window::Window()
{
	/*Config sizeConfig;
	sizeConfig.ConfigSystemStartup("config.txt");


	offsetFromWindowsDesktop = 50;
	windowPhysicalWidth = winPhysWidth;
	windowPhysicalHeight = winPhysHeight;
	viewLeft = 0.0;
	viewRight = winWidth;
	viewBottom = 0.0;
	viewTop = viewRight * static_cast<double>(windowPhysicalHeight) / static_cast<double>(windowPhysicalWidth);
	APP_NAME = "Win32 D3D Test App";

	g_hWnd = nullptr;
	g_displayDeviceContext = nullptr;
	g_openGLRenderingContext = nullptr;*/

}

Window::~Window() {

}

static RECT WindowGetRect(int width, int height, DWORD style) {
	RECT window_rect;
	window_rect.left = 0;
	window_rect.top = 0;
	window_rect.right = width;
	window_rect.bottom = height;

	// Adjust the size so the window is big enough with this style to allow the client
	// to be the size of window_rect
	::AdjustWindowRect(&window_rect, style, FALSE);

	return window_rect;
}

static HINSTANCE GetCurrentHINSTANCE() {
	return ::GetModuleHandle(NULL);
}

static LRESULT CALLBACK WindowsMessageHandlingProcedure(HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam) {
	unsigned char keyCode = (unsigned char)wParam;
	switch (wmMessageCode)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		g_theApp->SetIsQuitting(true);
		return 0;

	case WM_KEYDOWN:

		g_theApp->OnKeyDown(keyCode);

		break;

	case WM_KEYUP:

		g_theApp->OnKeyUp(keyCode);

		break;
	}

	return DefWindowProc(windowHandle, wmMessageCode, wParam, lParam);
}

bool Window::RegisterGameWindowClass() {
	//Log("Registering Window Class");

	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));

	// Setup the definition for this window class
	wc.cbSize = sizeof(WNDCLASSEX);

	// This sets that it will redraw for vertical or horizontal changes
	// and it also owns its own device context handle (more effecient if we're
	// drawing to this window a lot - which we will be.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// The Windows Messaeg Pump - handles messages for this window type.
	wc.lpfnWndProc = WindowsMessageHandlingProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetCurrentHINSTANCE();

	// Default icon for this window (can be set later)
	wc.hIcon = NULL;
	wc.hIconSm = NULL;

	// Cursor to use (can be set later if needed)
	wc.hCursor = ::LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
	wc.hbrBackground = (HBRUSH)0;
	wc.lpszMenuName = NULL;

	// Name to use when creating windows so it knows to use this class
	wc.lpszClassName = WNDCLASS_GAME_NAME;

	ATOM result = RegisterClassEx(&wc);
	if (NULL == result) {
		//Logf("Failed to register window class [ErrNo: %u]", GetLastError());
		return false;
	}

	return true;
}

void Window::UnregisterGameWindowClass() {
	UnregisterClass(WNDCLASS_GAME_NAME, GetCurrentHINSTANCE());
}

HWND Window::CreateTheWindow(char const *title, int x, int y, int res_x, int res_y) {
	DWORD extended_style = 0;
	DWORD style = 0U;
	APP_NAME = title;
	SetProcessDPIAware();
	// If you want a "window" - this gives it the caption bar, a sysmenu, and a border.
	style |= (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER);

	// this style will instead make it borderless - good for fullscreen windows.
	// MUTUALLY EXCLUSIVE WITH ABOVE
	// style |= WS_POPUP;

	// Window starts invisible by default - this will allow it to be visible
	style |= WS_VISIBLE;

	RECT win_rect = WindowGetRect(res_x, res_y, style);

	x += win_rect.left;
	y += win_rect.top;
	int w = win_rect.right - win_rect.left;
	int h = win_rect.bottom - win_rect.top;

	HWND hwnd = CreateWindowExA(extended_style, // Extended style (not used)
		WNDCLASS_GAME_NAME_LPCSTR,                       // Windows Class to use
		title,                                    // title      
		style,                                    // Style to start this with
		x, y,                                     // x, y of actual window (not client rect)
		w, h,                                     // width and height of actual window
		NULL,                                     // my parent (not used in this example)
		NULL,                                     // my menu (not used in this example)
		GetCurrentHINSTANCE(),                    // hinstance this window belongs too
		nullptr);                                // passed as lParam in WM_CREATE message (good place to store a pointer to a window object if you class'ify this)

	if (NULL == hwnd) {
		DWORD error = GetLastError();
		DebuggerPrintf("Failed to create window:  Error[%u]", error);
	}

	g_hWnd = hwnd;
	return hwnd;
}


bool Window::Open()
{
	bool success = ShowWindow(g_hWnd, SW_SHOW) != 0;
	return success;
}

void Window::Close() {

}

unsigned char Window::ProcessMessages() {
	MSG queuedMessage;
	for (;; )
	{
		const BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage);
	}
	return '2';
}

bool Window::IsOpen() const {
	return true;
}

bool Window::IsClosed() const {
	return true;
}


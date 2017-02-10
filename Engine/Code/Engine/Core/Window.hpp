#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <cassert>
#include <crtdbg.h>
#include <string>


#include "Engine/Math/AABB2.hpp"
#include "Game/App.hpp"
#include "Game/GameCommon.hpp"


class Window {
public:
	Window();
	~Window();
	bool RegisterGameWindowClass();
	void UnregisterGameWindowClass();
	HWND CreateTheWindow(char const *title, int x, int y, int res_x, int res_y);

	void SetClientSize(int width, int height);

	bool Open();

	void Close();

	unsigned char ProcessMessages();

	bool IsOpen() const;
	bool IsClosed() const;

	AABB2 worldBoundingBox; //TODO consider removing
	HWND g_hWnd;
	HDC g_displayDeviceContext;
	HGLRC g_openGLRenderingContext;
	const char* APP_NAME;

private:

	int offsetFromWindowsDesktop;
	int windowPhysicalWidth;
	int windowPhysicalHeight;
	double viewLeft;
	double viewRight;
	double viewBottom;
	double viewTop;
	

	
	


	

};
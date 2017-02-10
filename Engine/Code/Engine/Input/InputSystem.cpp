#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Engine/Input/InputSystem.hpp"


InputSystem::InputSystem():
	m_hideMouseCursorWhenFocused(true)
	,m_isMouseCursorHidden(false)
	,m_doesAppHaveFocus(true)
{
	for (int i = 0; i < NUM_KEYS; i++) {
		m_keyStates[i].m_isDown = false;
		m_keyStates[i].m_wasDown = false;
	}
	
	for (int xboxControllerID = 0; xboxControllerID < MAX_CONTROLLERS; ++xboxControllerID)
		m_controllers[xboxControllerID].m_controllerNum = xboxControllerID;
}

void InputSystem::UpdateInput() {

	if (!m_doesAppHaveFocus) {
		Sleep(100);
	}

	for (int xboxIndex = 0; xboxIndex < MAX_CONTROLLERS; xboxIndex++) {
		m_controllers[xboxIndex].Update();
	}

	for (int keyIndex = 0; keyIndex < NUM_KEYS; keyIndex++)
		m_keyStates[keyIndex].m_wasDown = m_keyStates[keyIndex].m_isDown;

	RunMessagePump();

}

bool InputSystem::IsKeyDown(int keyCode) const {
	return m_keyStates[keyCode].m_isDown;
}

bool InputSystem::WasKeyJustPressed(int keyCode) const {
	if (m_keyStates[keyCode].m_isDown == false)
		return false;
	return  m_keyStates[keyCode].m_wasDown != m_keyStates[keyCode].m_isDown;
}

void InputSystem::OnKeyDown(int keyCode) {
	m_keyStates[keyCode].m_isDown = true;
}

void InputSystem::OnKeyUp(int keyCode) {
	m_keyStates[keyCode].m_isDown = false;
}

const XboxController& InputSystem::GetControllerState(int controllerNum) {
	return m_controllers[controllerNum];
}

Vector2 InputSystem::GetMouseScreenCoords() const {
	POINT cursorScreenPosInts;
	GetCursorPos(&cursorScreenPosInts);
	Vector2 fCursorPosFloats((float)cursorScreenPosInts.x, (float)cursorScreenPosInts.y);
	return fCursorPosFloats;
}

void InputSystem::SetMouseCursorPosition(const Vector2& newMouseScreenCoords) {

	int x = (int)newMouseScreenCoords.x;
	int y = (int)newMouseScreenCoords.y;
	SetCursorPos(x, y);
}

Vector2 InputSystem::GetScreenSize() const {
	HWND desktopWindowHandle = GetDesktopWindow();
	RECT desktopRect;
	GetWindowRect(desktopWindowHandle, &desktopRect);
	Vector2 screenSize;
	screenSize.x = (float)desktopRect.right - desktopRect.left;
	screenSize.y = (float)desktopRect.bottom - desktopRect.top;
	return screenSize;
}

void InputSystem::OnAppGainedFocus() {
	m_hideMouseCursorWhenFocused = true;
	m_doesAppHaveFocus = true;
	if (m_hideMouseCursorWhenFocused)
		HideMouseCursor();
}

void InputSystem::OnAppLostFocus() {
	m_hideMouseCursorWhenFocused = false;
	m_doesAppHaveFocus = false;
	ShowMouseCursor();
}

bool InputSystem::DoesAppHaveFocus() const
{
	return m_hideMouseCursorWhenFocused;
}

void InputSystem::HideMouseCursor() {
	while (ShowCursor(FALSE) >= 0);
}

void InputSystem::ShowMouseCursor() {
	while (ShowCursor(TRUE) < 0);
}

void InputSystem::SetMouseCursorHiddenWHenFocused(bool hideMouseWhenNotFocused) {
	m_hideMouseCursorWhenFocused = hideMouseWhenNotFocused;
	if (m_hideMouseCursorWhenFocused && m_doesAppHaveFocus) {
		HideMouseCursor();
	}
}

void InputSystem::RunMessagePump() {
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
}



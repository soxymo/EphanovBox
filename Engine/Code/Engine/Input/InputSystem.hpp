#pragma once
#include "Engine/Input/XboxController.hpp"
enum KeyCode {
	KEY_ENTER = 0x0D,
	KEY_ESCAPE = 0x1B, //;same as VK_ESCAPE
	KEY_PAUSE = 0x13,
	KEY_LEFT = 0x25,
	KEY_UP = 0x26,
	KEY_RIGHT = 0x27,
	KEY_DOWN = 0x28,
	KEY_SHIFT = 0x10,
	KEY_CTRL = 0x11,
	KEY_LMOUSE = 0x01,
	KEY_RMOUSE = 0x02,
	KEY_F5 = 0x74,
	KEY_F6 = 0x75,
	KEY_BACKSPACE = 0x08,
	KEY_TILDE = 126
};

class KeyState {
public:
	//add constructor with default parameters
	bool m_isDown;
	bool m_wasDown;
};

const int NUM_KEYS = 256;
const int MAX_CONTROLLERS = 4;

class InputSystem {
private:
	KeyState m_keyStates[NUM_KEYS];
	XboxController m_controllers[MAX_CONTROLLERS];
	bool m_hideMouseCursorWhenFocused;
	bool m_doesAppHaveFocus;
	bool m_isMouseCursorHidden;

public:
	InputSystem();
	void UpdateInput();
	bool IsKeyDown(int keyCode) const;
	bool WasKeyJustPressed(int keyCode) const;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	const XboxController& GetControllerState(int controllerNum);
	Vector2 GetMouseScreenCoords() const;
	void SetMouseCursorPosition(const Vector2& newMouseScreenCoords);
	Vector2 GetScreenSize() const;
	void OnAppGainedFocus();
	void OnAppLostFocus();
	bool DoesAppHaveFocus() const;
	void HideMouseCursor();
	void ShowMouseCursor();
	void SetMouseCursorHiddenWHenFocused(bool hideMouseWhenNotFocused);
private:
	void RunMessagePump();
	
};
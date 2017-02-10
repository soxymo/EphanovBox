#pragma once
#include "Engine/Math/Vector2.hpp"

struct XboxButtonState {
public:
	bool m_pressedDown;
	bool m_justChanged;
};

struct XboxStickState {
public:
	Vector2 m_normalizedPos;
	float m_direction;
	float m_magnitude;
};

enum XboxButton{
	D_UP,
	D_DOWN,
	D_LEFT,
	D_RIGHT,
	START_BUTTON,
	SELECT_BUTTON,
	L_STICK_CLICK,
	R_STICK_CLICK,
	L_BUMPER,
	R_BUMPER,
	A_BUTTON,
	B_BUTTON,
	X_BUTTON,
	Y_BUTTON,
	NUM_BUTTONS
};

enum XboxStick {
	L_STICK,
	R_STICK,
	NUM_STICKS
};

class XboxController {
	friend class InputSystem;
public:
	int m_controllerNum;
	XboxButtonState m_buttonArray[NUM_BUTTONS];
	XboxStickState m_stickArray[NUM_STICKS];
	

	XboxController();
	
	bool IsButtonPressed(XboxButton button);
	bool HasButtonJustChanged(XboxButton button);
	bool WasButtonJustPressed(XboxButton button);
	Vector2 GetStickVector(XboxStick stick);
	float GetStickMagnitude(XboxStick stick);
	float GetStickDirectionDegrees(XboxStick stick);
	bool IsConnected();

private:
	void Update();
	bool m_isConnected;
	void UpdateButtonStatus(int buttonIndex, int bitMask, int rawInput);
	void UpdateStickState(XboxStick stickIndex, int xRaw, int yRaw);


	
};

#include "Engine/Input/XboxController.hpp"
#include <Windows.h>
#include <Xinput.h> // include the Xinput API
#pragma comment( lib, "xinput9_1_0" ) // Link in the xinput.lib static library // #Eiserloh: Xinput 1_4 doesn't work in Windows 7; using 9_1_0 explicitly
#include "Engine/Math/MathUtils.hpp"


const int buttonMaskArray[14] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
};

const int MAX_STICK_VALUE = 32768;
const float DEAD_ZONE_ARRAY[2] = {
	(float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE/(float)MAX_STICK_VALUE,
	(float)XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE/(float)MAX_STICK_VALUE
};

const float OUTER_DEAD_ZONE = .92f;


XboxController::XboxController()
	: m_controllerNum( 0 ),
	m_isConnected(false)
{
	for (int buttonIndex = 0; buttonIndex < NUM_BUTTONS; buttonIndex++) {
		m_buttonArray[buttonIndex].m_pressedDown = false;
		m_buttonArray[buttonIndex].m_justChanged = false;
	}

	for (int i = 0; i < 2; i++) {
		m_stickArray[i].m_normalizedPos = Vector2(0.f, 0.f);
		m_stickArray[i].m_normalizedPos = Vector2(0.f, 0.f);
		m_stickArray[i].m_direction = 0.f;
		m_stickArray[i].m_magnitude = 0.f;
	}
}

void XboxController::Update()
{
	XINPUT_STATE xboxControllerState;
	memset(&xboxControllerState, 0, sizeof(xboxControllerState));
	DWORD errorStatus = XInputGetState(m_controllerNum, &xboxControllerState);
	m_isConnected = false;
	if (errorStatus == ERROR_SUCCESS)
	{
		m_isConnected = true;
		int rawButtonInput = xboxControllerState.Gamepad.wButtons;
		for (int buttonIndex = 0; buttonIndex < NUM_BUTTONS; buttonIndex++) {
			UpdateButtonStatus(buttonIndex, buttonMaskArray[buttonIndex], rawButtonInput);	
		}
		UpdateStickState(L_STICK, xboxControllerState.Gamepad.sThumbLX, xboxControllerState.Gamepad.sThumbLY);
		UpdateStickState(R_STICK, xboxControllerState.Gamepad.sThumbRX, xboxControllerState.Gamepad.sThumbRY);
	}
// 	else if (errorStatus == ERROR_DEVICE_NOT_CONNECTED) {
// 		return false;
// 	}
// 	else {//unknown condition, kill it!!!!
// 		return false;
// 	}
}

bool XboxController::IsButtonPressed(XboxButton button) {
	return m_buttonArray[button].m_pressedDown;
}

bool XboxController::HasButtonJustChanged(XboxButton button) {
	return m_buttonArray[button].m_justChanged;
}

bool XboxController::WasButtonJustPressed(XboxButton button) {
	return m_buttonArray[button].m_pressedDown && m_buttonArray[button].m_justChanged;
}

Vector2 XboxController::GetStickVector(XboxStick stick) {
	return m_stickArray[stick].m_normalizedPos;
}

float XboxController::GetStickMagnitude(XboxStick stick) {
	return m_stickArray[stick].m_magnitude;
}

float XboxController::GetStickDirectionDegrees(XboxStick stick){
	return m_stickArray[stick].m_direction;
}


bool XboxController::IsConnected() {
	return m_isConnected;
}

void XboxController::UpdateButtonStatus(int buttonIndex, int bitMask, int rawInput) {
	bool buttonIsPressed = (rawInput & bitMask) != 0;
	if (m_buttonArray[buttonIndex].m_pressedDown != buttonIsPressed)
		m_buttonArray[buttonIndex].m_justChanged = true;
	else
		m_buttonArray[buttonIndex].m_justChanged = false;
	m_buttonArray[buttonIndex].m_pressedDown = buttonIsPressed;
}

void XboxController::UpdateStickState(XboxStick stickIndex, int xRaw, int yRaw) {
	Vector2 normalizedPosition( (float)xRaw / (float)MAX_STICK_VALUE, (float)yRaw / (float)MAX_STICK_VALUE);
	float direction = normalizedPosition.CalcHeadingDegrees();
	float magnitude = normalizedPosition.CalcLength();

	if (magnitude < DEAD_ZONE_ARRAY[stickIndex])
		magnitude = DEAD_ZONE_ARRAY[stickIndex];

	if (magnitude > OUTER_DEAD_ZONE)
		magnitude = OUTER_DEAD_ZONE;

	magnitude = RangeMapFloat(magnitude, DEAD_ZONE_ARRAY[stickIndex], OUTER_DEAD_ZONE, 0.f, 1.f);
	m_stickArray[stickIndex].m_normalizedPos.SetLengthAndHeadingDegrees(magnitude, direction);
	m_stickArray[stickIndex].m_magnitude = magnitude;
	m_stickArray[stickIndex].m_direction = direction;
}


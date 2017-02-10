#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Engine/Renderer/SimpleRenderer.hpp"

const float CURSOR_BLINK_INTERVAL = .5f;


class Console {
public:
	Console(SimpleRenderer* simpRenderer);
	~Console();

	void UpdateCursor(float deltaSeconds);
	void Render();
	void SetRenderer(SimpleRenderer* rendererToSet);
	void UpdateTextBuffer(int keycode);
	void SetIsActive(bool newActiveState);
	bool GetIsActive();
	void ToggleIsActive();
	void ConsolePrintf(char *format, ...);

private:
	void ExecuteCommnd();
	void RenderCursor();

public:
	std::vector<std::string> backList;
	std::string activeString;
	SimpleRenderer* fontRenderer;


private:
	bool isActive;
	Font* font;
	Vector2 startingPoint;
	float cursorBlinkTimer;
	bool shouldRenderCursor;
};
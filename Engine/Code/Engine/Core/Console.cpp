#include "Engine/Core/Console.hpp"
#include "Engine/Renderer/Font.h"
#include "Game/GameCommon.hpp"




Console::Console(SimpleRenderer* simpRenderer)
	:isActive(false)
	, fontRenderer(simpRenderer)
	, cursorBlinkTimer(0.f)
	, shouldRenderCursor(true)
{
	
	font = new Font("put real text in here");
	activeString = "What do you think about the stars in the sky?";
	startingPoint.SetXY(0, 10);
}




void Console::UpdateCursor(float deltaSeconds) {
	cursorBlinkTimer += deltaSeconds;
	if (cursorBlinkTimer > CURSOR_BLINK_INTERVAL) {
		cursorBlinkTimer = 0;
		shouldRenderCursor = !shouldRenderCursor;
	}
}

void Console::Render() {
	if (fontRenderer == nullptr || !isActive) {
		return;
	}

	fontRenderer->drawAABB2(AABB2(0.f,0.f, 1600.f, 900.f), Rgba(0.f,0.f,0.f, .5f)); //TODO don't hardcore this full screen overlay

	fontRenderer->DrawText2D(startingPoint, 1.f, Rgba(), font, activeString);
	
	int rowCounter = 1;
	for (int i = backList.size()-1; i >= 0; i--) {
		float yStartOffset = font->lineHeight*((float)rowCounter);
		rowCounter++; \
			Vector2 drawPoint = startingPoint + Vector2(0, yStartOffset);
		fontRenderer->DrawText2D(drawPoint, 1.f, Rgba(), font, backList[i]);
	}

	RenderCursor();
	
}

void Console::SetRenderer(SimpleRenderer* rendererToSet) {
	fontRenderer = rendererToSet;
}

void Console::UpdateTextBuffer(int keycode) {
	if (!isActive) {
		return;
	}

	if (keycode == KEY_ENTER) {
		ExecuteCommnd();
		return;
	}
	else if (keycode == KEY_SHIFT) {
		return;
	}
	else if (keycode == KEY_BACKSPACE) {
		if (activeString.size() > 0) {
			activeString.pop_back();
		}
		return;
	}

	if (!g_theInputSystem->IsKeyDown(KEY_SHIFT) && (char)keycode != ' ') {
		keycode += 32;
	}
	activeString += (char)keycode;
	cursorBlinkTimer = 0;
}

void Console::SetIsActive(bool newActiveState) {
	isActive = newActiveState;
}

bool Console::GetIsActive()
{
	return isActive;
}

void Console::ToggleIsActive() {
	isActive = !isActive;
}

void Console::ConsolePrintf(char *format, ...) {
	char buffer[1000]; //that should be big enough, right
	va_list vars;
	va_start(vars, format);
	vsprintf(buffer, format, vars);
	va_end(vars);

	activeString = buffer;
	backList.push_back(activeString);
	activeString = "";

	
}

void Console::ExecuteCommnd() {

	if (activeString == "clear") {
		backList.clear();
		activeString = "";
		return;
	}

	if (activeString == "quit") {
		g_theApp->SetIsQuitting(true);
		return;
	}

	if (activeString == "help") {
		backList.push_back(activeString);
		backList.push_back("You can type 'help' to get help. Also 'clear' clears the log");
		activeString = "";
	}
	else {

		backList.push_back(activeString);
		activeString = "";
	}

	//parse command here
	

	
}

void Console::RenderCursor() {
	if (!shouldRenderCursor) {
		return;
	}

	std::string cursorText = "|";
	Vector2 cursorPosition = startingPoint + Vector2(font->CalculateTextWidth(activeString), 1.f);
	fontRenderer->DrawText2D(cursorPosition, 1.f, Rgba(), font, cursorText);
}


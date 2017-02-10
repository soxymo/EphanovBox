#include "Game/Game.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Input/InputSystem.hpp"

Game* g_asteroidsGame = nullptr;

Game::Game(AABB2 theWorldBox) :m_isGamePaused(false)
,m_slowMode(false)
{
	m_worldBox = theWorldBox;
}

Game::~Game() {

}

void Game::Update(float deltaSeconds) {
	
	if (m_slowMode)
		deltaSeconds *= 0.1f;

	if (m_isGamePaused)
		deltaSeconds *= 0.f;

    //TESTING STUFF
// 	if (g_theInputSystem->IsKeyDown('K'))
// 		DebuggerPrintf("is key down\n");
// 	if (g_theInputSystem->WasKeyJustPressed('K'))
// 		DebuggerPrintf("just pressed down\n");
// 	XboxController xbox = g_theInputSystem->GetControllerState(0);
// 	if (xbox.IsConnected()) {
// 		Vector2 stickVector = xbox.GetStickVector(R_STICK);
// 		DebuggerPrintf("x=%f, y=%f", stickVector.x, stickVector.y);
// 	}
}

void Game::Render(){
	g_theRenderer->SetOrtho(m_worldBox);
	g_theRenderer->clearToBlack();
}

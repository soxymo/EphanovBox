#include "Game/Game.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Input/InputSystem.hpp"

Game* g_asteroidsGame = nullptr;

Game::Game(AABB2 theWorldBox) :m_isGamePaused(false)
,m_slowMode(false)
,m_camera(Camera3D(Vector3(-5.f, 0.5f, 0.5f)))
{
	m_worldBox = theWorldBox;
}

Game::~Game() {

}

void Game::Update(float deltaSeconds) {
	
    UpdatePlayerMovement(deltaSeconds);

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

void Game::UpdatePlayerKeyboardMovement(float deltaSeconds)
{
    Vector3 cameraForwardXY = m_camera.GetForwardXY();
    Vector3 cameraLeftXY = m_camera.GetLeftXY();

    const float PLAYER_MOVE_BLOCKS_PER_SECOND = 4.5f;
    Vector3 moveDirectionThisFrame(0.f, 0.f, 0.f);

    if (g_theInputSystem->IsKeyDown(' '))
        moveDirectionThisFrame.z += 1.0f;

    if (g_theInputSystem->IsKeyDown('Z'))
        moveDirectionThisFrame.z -= 1.0f;

    if (g_theInputSystem->IsKeyDown('W'))
        moveDirectionThisFrame += cameraForwardXY;

    if (g_theInputSystem->IsKeyDown('S'))
        moveDirectionThisFrame -= cameraForwardXY;

    if (g_theInputSystem->IsKeyDown('A'))
        moveDirectionThisFrame += cameraLeftXY;

    if (g_theInputSystem->IsKeyDown('D'))
        moveDirectionThisFrame -= cameraLeftXY;

    moveDirectionThisFrame.Normalize();

    if (g_theInputSystem->IsKeyDown(KEY_SHIFT))
        moveDirectionThisFrame *= 8.f;

    Vector3 moveThisFrame = moveDirectionThisFrame * (PLAYER_MOVE_BLOCKS_PER_SECOND * deltaSeconds);
    m_camera.m_position += moveThisFrame;
}

void Game::UpdatePlayerMovement(float deltaSeconds)
{
    UpdatePlayerKeyboardMovement(deltaSeconds);
}

void Game::Render(){
	g_theRenderer->SetOrtho(m_worldBox);
	g_theRenderer->clearToBlack();

    g_theRenderer->SetPerspective(50.f, 16.f / 9.f, 0.01f, 1000.f);

    // Put +Z up, +X forward, and +Y left (instead of default -Z forward, +X right, + Y up)
    g_theRenderer->RotateDrawFrame3D(-90.f, Vector3(1.f, 0.f, 0.f));
    g_theRenderer->RotateDrawFrame3D(+90.f, Vector3(0.f, 0.f, 1.f));


    // Anti-rotate to the camera's yaw, pitch, roll
    g_theRenderer->RotateDrawFrame3D(-m_camera.m_rollDegreesAboutX, Vector3(1.f, 0.f, 0.f));
    g_theRenderer->RotateDrawFrame3D(-m_camera.m_pitchDegreesAboutY, Vector3(0.f, 1.f, 0.f));
    g_theRenderer->RotateDrawFrame3D(-m_camera.m_yawDegreesAboutZ, Vector3(0.f, 0.f, 1.f));


    // Anti-translate to the camera's position (e.g. move world WEST to simulate camera is EAST)
    g_theRenderer->TranslateDrawFrame3D(m_camera.m_position * -1.f);

    g_theRenderer->renderAxis(10.0f);
    g_theRenderer->renderWireSphere(2.0, 10.0, 10.0);
}

#include "Game/Game.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Input/InputSystem.hpp"

Game* g_asteroidsGame = nullptr;

Game::Game(AABB2 theWorldBox) :m_isGamePaused(false)
,m_slowMode(false)
,m_camera(Camera3D(Vector3(-5.f, 0.5f, 0.5f)))
,myFloor(Vector3(0.f, 0.f, 1.f), 0)
,myPosXSide(Vector3(1.f, 0.f, 0.f), 10)
,myPosYSide(Vector3(0.f, 1.f, 0.f), 10)
,myNegXSide(Vector3(-1.f, 0.f, 0.f), 10)
,myNegYSide(Vector3(0.f, -1.f, 0.f), 10)
{
    g_theInputSystem->SetMouseCursorHiddenWHenFocused(true);
	m_worldBox = theWorldBox;
	
	bList.push_back(Ball());
	bList.push_back(Ball(Vector3(2,2, 8), Vector3(-2, -1, 0)));

}

Game::~Game() {

}

void Game::Update(float deltaSeconds) {
	
    UpdatePlayerMovement(deltaSeconds);
	for (unsigned int i = 0; i < bList.size(); i++) {

		bList[i].Update(deltaSeconds);
		BounceBallOffPlanes(deltaSeconds, bList[i]);
	}

	BouncOffBalls(bList[0], bList[1]);

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

void Game::BounceBallOffPlanes(float deltaSeconds, Ball& myBall)
{
    if (!myFloor.RealIsPointInFront(myBall.sphere.center - Vector3(0, 0, myBall.sphere.radius))) {
        myBall.sphere.center.z = myBall.sphere.radius;
        myBall.velocity.z *= -1;
		myBall.velocity.z *= .9f;
    }

    if (!myPosXSide.RealIsPointInFront(myBall.sphere.center + Vector3(myBall.sphere.radius, 0, 0))) {
        myBall.sphere.center.x = myPosXSide.m_distToOrigin - myBall.sphere.radius;
        myBall.velocity.x *= -1;
    }

	 if (!myPosYSide.RealIsPointInFront(myBall.sphere.center + Vector3(0, myBall.sphere.radius, 0))) {
		 //myBall.sphere.center.y = myPosYSide.m_distToOrigin - myBall.sphere.radius;
		 myBall.velocity.y *= -1;
	 }

	 if (!myNegXSide.RealIsPointInFront(myBall.sphere.center - Vector3(myBall.sphere.radius, 0, 0))) {
		 //myBall.sphere.center.x = -1.f*myNegXSide.m_distToOrigin + myBall.sphere.radius;
		 myBall.velocity.x *= -1;
	 }

	 if (!myNegYSide.RealIsPointInFront(myBall.sphere.center - Vector3( 0, myBall.sphere.radius, 0))) {
		 //myBall.sphere.center.y = -1.f* myNegYSide.m_distToOrigin + myBall.sphere.radius;
		 myBall.velocity.y *= -1;
	 }
}

void Game::BouncOffBalls(Ball& ball1, Ball& ball2) {

	if (!DoSpheresOverlap(ball1.sphere, ball2.sphere)) {
		return;
	}

	Vector3 displacementFromFirstToSecond = ball2.sphere.center - ball1.sphere.center;
	Vector3 directionFromFirstToSecond = displacementFromFirstToSecond;
	directionFromFirstToSecond.Normalize();
	float distance = displacementFromFirstToSecond.CalcLength();
	float overlapDistance = (ball1.sphere.radius + ball2.sphere.radius) - distance;
	Vector3 firstPositionCorrection = directionFromFirstToSecond * (-0.5f * overlapDistance);
	ball2.sphere.center -= firstPositionCorrection;
	ball1.sphere.center += firstPositionCorrection;
	float speedTowardSecond = DotProduct(ball1.velocity, directionFromFirstToSecond);
	if (speedTowardSecond > 0.f) {
		Vector3 velocityTowardSecond = speedTowardSecond * directionFromFirstToSecond;
		Vector3 velocityNotTowardSecond = ball1.velocity - directionFromFirstToSecond;
		ball1.velocity = ((-1.f * (ball1.elasticity * ball2.elasticity)) * velocityTowardSecond) + velocityNotTowardSecond;
		ball2.velocity = ((ball1.elasticity * ball2.elasticity) * velocityTowardSecond) + velocityNotTowardSecond;
	}



	/*if (!DoDisc2DsOverlap(ball1->m_disc, ball2->m_disc))
		return;

	Vector2 displacementFromFirstToSecond = ball2->m_disc.center - ball1->m_disc.center;
	Vector2 directionFromFirstToSecond = displacementFromFirstToSecond;
	directionFromFirstToSecond.Normalize();
	float distance = displacementFromFirstToSecond.CalcLength();
	float overlapDistance = (ball1->m_disc.radius + ball2->m_disc.radius) - distance;
	Vector2 firstPositionCorrection = directionFromFirstToSecond * (-0.5f * overlapDistance);
	ball2->m_disc.center -= firstPositionCorrection;
	ball1->m_disc.center += firstPositionCorrection;
	float speedTowardSecond = DotProduct(ball1->m_velocity, directionFromFirstToSecond);
	if (speedTowardSecond > 0.f)
	{
		Vector2 velocityTowardSecond = speedTowardSecond * directionFromFirstToSecond;
		Vector2 velocityNotTowardsSecond = ball1->m_velocity - directionFromFirstToSecond;
		//ball1->m_velocity = (-0.8f * velocityTowardSecond) + velocityNotTowardsSecond;
		ball1->m_velocity = ((-1.f * (ball1->m_elasticity * ball2->m_elasticity)) * velocityTowardSecond) + velocityNotTowardsSecond;
		//ball2->m_velocity = (0.8f * velocityTowardSecond) + velocityNotTowardsSecond;
		ball2->m_velocity = ((ball1->m_elasticity * ball2->m_elasticity) * velocityTowardSecond) + velocityNotTowardsSecond;
	}*/

}

void Game::UpdatePlayerMouseLook(float deltaSeconds)
{
    if (!g_theInputSystem->DoesAppHaveFocus())
        return; //Don't update player look angle from mouse when in not in focus!

    const float YAW_DEGREES_PER_MOUSE_MOVE = -0.02f;
    const float PITCH_DEGREES_PER_MOUSE_MOVE = 0.02f;

    Vector2 screenSize = g_theInputSystem->GetScreenSize();
    const Vector2 mouseRecenterPos = screenSize * 0.5f;
    Vector2 mouseScreenPos = g_theInputSystem->GetMouseScreenCoords();
    Vector2 mouseMoveSinceLastFrame = mouseScreenPos - mouseRecenterPos;

    g_theInputSystem->SetMouseCursorPosition(mouseRecenterPos);
    m_camera.m_yawDegreesAboutZ += YAW_DEGREES_PER_MOUSE_MOVE * mouseMoveSinceLastFrame.x;
    m_camera.m_pitchDegreesAboutY += PITCH_DEGREES_PER_MOUSE_MOVE * mouseMoveSinceLastFrame.y;
    m_camera.m_pitchDegreesAboutY = ClampWithin(m_camera.m_pitchDegreesAboutY, -89.9f, 89.9f);
}


void Game::UpdatePlayerKeyboardMovement(float deltaSeconds)
{
    Vector3 cameraForwardXY = m_camera.GetForwardXY();
    Vector3 cameraLeftXY = m_camera.GetLeftXY();

    const float PLAYER_MOVE_BLOCKS_PER_SECOND = 4.5f;
    Vector3 moveDirectionThisFrame(0.f, 0.f, 0.f);

    if (g_theInputSystem->IsKeyDown(' '))
        moveDirectionThisFrame.z += 1.0f;

    if (g_theInputSystem->IsKeyDown('Q'))
        moveDirectionThisFrame.z -= 1.0f;
	if (g_theInputSystem->IsKeyDown('E'))
		moveDirectionThisFrame.z += 1.0f;

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
    UpdatePlayerMouseLook(deltaSeconds);
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

	for (unsigned int i = 0; i < bList.size(); i++) {
		bList[i].Render();
	}

	
}

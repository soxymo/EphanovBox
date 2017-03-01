#pragma once
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Game/Camera3D.hpp"
#include "Game/Ball.h"
#include <iostream>
#include <vector>
#include "Game/SpringForce.hpp"

class Game {

private:
	AABB2 m_worldBox;
	bool m_slowMode;
	bool m_isGamePaused;
    Camera3D m_camera;

public:
	Game(AABB2 theWorldBox);
	~Game();
	void Update(float deltaSeconds);
    void BounceBallOffPlanes(float deltaSeconds, Ball* myBall);
	void BouncOffBalls(Ball* ball1, Ball* ball2);
    void UpdatePlayerMouseLook(float deltaSeconds);
    void UpdatePlayerKeyboardMovement(float deltaSeconds);
    void UpdatePlayerMovement(float deltaSeconds);
    void Render();

	Ball* completelyIsolatedBall;
	SpringForce spring;
	std::vector<Ball*> bList;

	
	
	
    Plane3 myFloor;
    Plane3 myPosXSide;
    Plane3 myPosYSide;
    Plane3 myNegXSide;
    Plane3 myNegYSide;
	Plane3 myCeiling;
};
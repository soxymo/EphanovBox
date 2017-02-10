#pragma once
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Input/InputSystem.hpp"


class Game {

private:
	AABB2 m_worldBox;
	bool m_slowMode;
	bool m_isGamePaused;

public:
	Game(AABB2 theWorldBox);
	~Game();
	void Update(float deltaSeconds);
	void Render();
};
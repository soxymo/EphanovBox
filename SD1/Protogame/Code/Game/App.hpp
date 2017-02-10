#pragma once
#include "Engine/Renderer/Renderer.hpp"
#include "Game/Game.hpp"
#include "Engine/Audio/Audio.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Math/AABB2.hpp"

const float NORMAL_FRAMERATE = 1.f / 60.f; //inspired by the code of Squrriel

class App;
extern App* g_theApp;

class App {
public:
	App(AABB2 screenBoundingBox);
	~App();

	void RunFrame();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnExitRequested();
	bool IsQuitting();
	void SetIsQuitting(bool val);
private:
	void Update(float deltaSeconds);
	void Render() const;
	float GetDeltaSeconds();
	
	bool m_isQuitting;


};
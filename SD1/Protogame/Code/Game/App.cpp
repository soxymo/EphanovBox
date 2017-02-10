#include "Game/App.hpp"
#include "Engine/Core/Time.hpp"

App* g_theApp = nullptr;


App::App(AABB2 screenBoundingBox):m_isQuitting(false) {

	g_theRenderer = new Renderer();
	g_theRenderer->EnableSmoothLines();

	g_theInputSystem = new InputSystem();
	g_theGame = new Game(screenBoundingBox);

	g_theAudioSystem = new AudioSystem();
	SoundID testSound = g_theAudioSystem->CreateOrGetSound("TestSound.mp3");
	g_theAudioSystem->PlaySound(testSound, 1.f);
}

App::~App() {
	delete g_theGame;
	delete g_theInputSystem;
	delete g_theRenderer;
	delete g_theAudioSystem;
}

void App::RunFrame() {
	g_theInputSystem->UpdateInput();
	float deltaSeconds = GetDeltaSeconds();
	g_theAudioSystem->Update();
	Update(deltaSeconds);
	Render();

	if (g_theInputSystem->IsKeyDown(KEY_ESCAPE))
		m_isQuitting = true;
}

void App::OnKeyDown(int keyCode) {
	g_theInputSystem->OnKeyDown(keyCode);
}

void App::OnKeyUp(int keyCode) {
	g_theInputSystem->OnKeyUp(keyCode);
}

bool App::IsQuitting() {
	return m_isQuitting;
}

void App::SetIsQuitting(bool val) {
	m_isQuitting = val;
}

void App::Update(float deltaSeconds) {
	g_theGame->Update(deltaSeconds);
}

void App::Render() const {
	g_theGame->Render();
}

float App::GetDeltaSeconds() {
	float currTime = (float)GetCurrentTimeSeconds();
	float lastFrameTime = currTime;
	float deltaSeconds = currTime - lastFrameTime;

	while (deltaSeconds < NORMAL_FRAMERATE *.999f) {
		currTime = (float)GetCurrentTimeSeconds();
		deltaSeconds = currTime - lastFrameTime;
	}

	if (deltaSeconds > NORMAL_FRAMERATE) {
		deltaSeconds = NORMAL_FRAMERATE;
	}
	return deltaSeconds;
}


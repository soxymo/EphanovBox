#pragma once
class Renderer;
class InputSystem;
class Game;
class AudioSystem;

extern Renderer* g_theRenderer;
extern InputSystem* g_theInputSystem;
extern Game* g_theGame;
extern AudioSystem* g_theAudioSystem;
extern bool g_isQuitting;
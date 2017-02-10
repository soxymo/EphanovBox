#pragma once
#include "Engine/Renderer/SpriteSheet.hpp"



enum SpriteAniMode
{
	SPRITE_ANIM_MODE_PLAY_TO_END,	// Play from time=0 to durationSeconds, then finish
	SPRITE_ANIM_MODE_LOOPING,		// Play from time=0 to end then repeat (never finish)
//  SPRITE_ANIM_MODE_PINGPONG, 	// optional, play forwards, backwards, forwards...
	NUM_SPRITE_ANIM_MODES
};



class SpriteAnimation {
private:
	bool m_isFinished;
	bool m_isPlaying;
	float m_durationSeconds;
	float m_elapsedSeconds;
	const SpriteSheet& m_spriteSheet;
	SpriteAniMode m_aniMode;
	int m_startSpriteIndex;
	int m_endSpriteIndex;


public:
	SpriteAnimation(const SpriteSheet& spriteSheet, float durationSeconds,
		SpriteAniMode playbackMode, int startSpriteIndex, int endSpriteIndex);

	~SpriteAnimation();
	void Update(float deltaSeconds);
	AABB2 GetCurrentTexCoords() const;	// Based on the current elapsed time
	Texture* GetTexture() const;
	void Pause();					// Starts unpaused (playing) by default
	void Resume();				// Resume after pausing
	void Reset();					// Rewinds to time 0 and starts (re)playing
	bool IsFinished() const { return m_isFinished; };
	bool IsPlaying() const { return m_isPlaying; };
	float GetDurationSeconds() const { return m_durationSeconds; };
	float GetSecondsElapsed() const { return m_elapsedSeconds; };
	float GetSecondsRemaining() const;
	float GetFractionElapsed() const;
	float GetFractionRemaining() const;
	void SetSecondsElapsed(float secondsElapsed);	    // Jump to specific time
	void SetFractionElapsed(float fractionElapsed);    // e.g. 0.33f for one-third in


};
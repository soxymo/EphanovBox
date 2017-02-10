#include "Engine/Renderer/SpriteAnimation.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"




SpriteAnimation::SpriteAnimation(const SpriteSheet& spriteSheet, float durationSeconds, SpriteAniMode playbackMode, int startSpriteIndex, int endSpriteIndex)
	:m_spriteSheet(spriteSheet)
	,m_isFinished(false)
	,m_isPlaying(true)
	,m_elapsedSeconds(0.f)
	,m_durationSeconds(durationSeconds)
	,m_aniMode(playbackMode)
	,m_startSpriteIndex(startSpriteIndex)
	,m_endSpriteIndex(endSpriteIndex)
{

}

SpriteAnimation::~SpriteAnimation() {

}

void SpriteAnimation::Update(float deltaSeconds) {
	if (m_isPlaying) {
		m_elapsedSeconds += deltaSeconds;
		if (m_elapsedSeconds >= m_durationSeconds) { //fix always looping;
			if(m_aniMode== SPRITE_ANIM_MODE_LOOPING)
				m_elapsedSeconds = 0.f;
			if (m_aniMode == SPRITE_ANIM_MODE_PLAY_TO_END) {
				m_isPlaying = false;
				m_isFinished = true;
			}
		}
	}
}

AABB2 SpriteAnimation::GetCurrentTexCoords() const {
	int currSpriteIndex = (int)RangeMapFloat(m_elapsedSeconds, 0.f, m_durationSeconds, (float)m_startSpriteIndex, (float)m_endSpriteIndex + 1);
	return m_spriteSheet.GetTexCoordsForSpriteIndex(currSpriteIndex);
}

Texture* SpriteAnimation::GetTexture() const {
	return m_spriteSheet.GetSheetTexture();
}

void SpriteAnimation::Pause() {
	m_isPlaying = false;
}

void SpriteAnimation::Resume() {
	m_isPlaying = true;
}

void SpriteAnimation::Reset() {
	m_elapsedSeconds = 0.f;
}

float SpriteAnimation::GetSecondsRemaining() const {
	return m_durationSeconds - m_elapsedSeconds;
}

float SpriteAnimation::GetFractionElapsed() const {
	ASSERT_OR_DIE(m_durationSeconds != 0.f, "Duration of animation is 0.f");
	return m_elapsedSeconds / m_durationSeconds;
}

float SpriteAnimation::GetFractionRemaining() const {
	ASSERT_OR_DIE(m_durationSeconds != 0.f, "Duration of animation is 0.f");
	return GetSecondsRemaining() / m_durationSeconds;
}

void SpriteAnimation::SetSecondsElapsed(float secondsElapsed) {
	m_elapsedSeconds = secondsElapsed;
}

void SpriteAnimation::SetFractionElapsed(float fractionElapsed) {
	m_elapsedSeconds = fractionElapsed * m_durationSeconds;
}

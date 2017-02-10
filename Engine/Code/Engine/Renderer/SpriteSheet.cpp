#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Renderer/Renderer.hpp"

SpriteSheet::SpriteSheet(const std::string& imageFilePath, int tilesWide, int tilesHigh, Renderer* globalRenderer) {
	m_spriteSheetTexture = globalRenderer->CreateOrGetTexture(imageFilePath);
	m_spriteLayout.SetXY(tilesWide, tilesHigh);
}

AABB2 SpriteSheet::GetTexCoordsForSpriteCoords(int spriteX, int spriteY) const {
	Vector2 topLeftPoint(spriteX / (float)m_spriteLayout.x, spriteY / (float)m_spriteLayout.y);
	Vector2 bottomRightPoint((spriteX + 1) / (float)m_spriteLayout.x, (spriteY + 1) / (float)m_spriteLayout.y);
	return AABB2(topLeftPoint, bottomRightPoint);
}

AABB2 SpriteSheet::GetTexCoordsForSpriteIndex(int spriteIndex) const {
	int spriteX = spriteIndex % m_spriteLayout.x;
	int spriteY = spriteIndex / m_spriteLayout.x;
	return GetTexCoordsForSpriteCoords(spriteX, spriteY);
}

int SpriteSheet::GetNumSprites() const {
	return m_spriteLayout.x * m_spriteLayout.y;
}

Texture* SpriteSheet::GetSheetTexture() const
{
	return m_spriteSheetTexture;
}


#pragma once
//#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Math/AABB2.hpp"
#include <string>
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Math/IntVector2.hpp"

class Renderer;

class SpriteSheet {
public:
	SpriteSheet(const std::string& imageFilePath, int tilesWide, int tilesHigh, Renderer* globalRenderer);
	AABB2 GetTexCoordsForSpriteCoords(int spriteX, int spriteY) const; // mostly for atlases
	AABB2 GetTexCoordsForSpriteIndex(int spriteIndex) const;
	int GetNumSprites() const;
	Texture* GetSheetTexture() const;

private:
	Texture* 	m_spriteSheetTexture;	// Image with grid-based layout of sub-images
	IntVector2	m_spriteLayout;		// # of sprites across, and down, on the sheet

};
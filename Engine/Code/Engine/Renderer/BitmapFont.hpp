#pragma once

#include "Engine/Renderer/SpriteSheet.hpp"


class Renderer;
class BitmapFont {
	friend class Renderer;
public:
	AABB2 GetTexCoordsForGlyph(int glyphUnicode) const;
	float GetGlyphAspect(int glyphUnicode) const { glyphUnicode;  1.0f; };
private:
	BitmapFont(const std::string& bitmapFontName);

	SpriteSheet* m_spriteSheet;
	
};
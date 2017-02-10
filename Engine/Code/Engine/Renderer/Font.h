#pragma once
#include <iostream>
#include <map>

typedef unsigned int uint;

class Texture2D;

struct glyphInfo {
	uint id;
	uint x;
	uint y;
	uint width;
	uint height;
	uint xoffset;
	uint yoffset;
	uint xadvance;
};

const std::string SUFFIX_RGX = "=-?\\d+";


class Font {

public:
	Font();
	Font(std::string filename);
	bool LoadFontFromFile(std::string filename);
	float CalculateTextWidth(std::string text, float scale = 1.0f);
	glyphInfo* GetGlyph(const char c);

public:
	char const* name;
	char const* textureFilepath;

	Texture2D* glyphTextures;

	uint size;
	uint lineHeight;
	uint scaleW;
	uint scaleH;
	uint pages;
	bool bodl;
	bool italic;

	std::map<int, glyphInfo> glyphMap;
	std::map<std::pair<int, int>, int> kernings;

private:
	int ReadAndGetInt(std::string keyName, std::string textLine);

	
};

/*
float GetTextWidht(Font* font, char const* text) {
	uint cursor = 0;
	char const* c = text;
	int prev_char_code = -1;

	while (c != NULL) {
		glyphInfo const* glyph = font->get_glyph(*c);

		if (glyph == nullptr) {
			glyph = font->get_invalid_glyph();
		}

		cursor += glyph->xadvance;
		prev_char_code = *c;
		++c;

		//move cursor forward
		int kerning = font->get_kerning(prev_char_code, *c);
		cursor += kerning;
	}

	return cursor;
}*/


/*
float DrawText(Font* font, char const* text) {
	uint cursor = 0;
	char const* c = text;
	int prev_char_code = -1;

	//TODO create one vertex buffer to make drawing not as slow

	while (c != NULL) {
		glyphInfo const* glyph = font->get_glyph(*c);

		if (glyph == nullptr) {
			glyph = font->get_invalid_glyph();
		}

		//get glyph positions
		Vector2 bottom_left;
		Vector2 top_right;
		
		Vector2 top_left = cursor + Vector2(glyph->xoffset, -glyph->yoffset);
		bottom_left = top_left + Vector2(0, -glyph->height);
		top_right = top_left + Vector2(glyph->width, 0);
		Vector2 bottom_right = bottom_left + Vector2(glyph->width, 0);

		Vector2 uv_top_left = Vector2(glyph->x / font->scale_w, glyph->y / font->scale_h);
		Vector2 uv_bottom_left = top_left + Vector2(0, glyph->height / font->scale_h);
		Vector2 uv_top_right = top_left + Vector2(glyph->width / font->scale_w, 0);

		//draw this guy,
		draw_quad2D

		cursor += glyph->xadvance;
		prev_char_code = *c;
		++c;

		//move cursor forward
		int kerning = font->get_kerning(prev_char_code, *c);
		cursor += kerning;
	}

	return cursor;
}
*/
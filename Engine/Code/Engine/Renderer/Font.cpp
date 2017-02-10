#include "Engine/Renderer/Font.h"
#include "Engine/RHI/Texture2D.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <regex>


using namespace std;

Font::Font() {

}

Font::Font(std::string filename) {
	LoadFontFromFile("data/font/DroidSans32.fnt");
}

bool Font::LoadFontFromFile(std::string filename) {

	std::string line;
	ifstream configFile;
	configFile.open(filename);
	if (!configFile.is_open()) {
		return false;
	}
	
	name = "data/font/DroidSans32.fnt"; //TODO make this not hard coded
	textureFilepath = "data/font/DroidSans32_0.png";


	std::getline(configFile, line);
	size = ReadAndGetInt("size", line);

	std::getline(configFile, line);
	lineHeight = ReadAndGetInt("lineHeight", line);
	scaleW = ReadAndGetInt("scaleW", line);
	scaleH = ReadAndGetInt("scaleH", line);
	pages = ReadAndGetInt("pages", line);

	
	//skip some lines to get to the meat
	std::getline(configFile, line);
	std::getline(configFile, line);

	while (getline(configFile, line)) {
		glyphInfo glyph;
		glyph.id = ReadAndGetInt("id", line);
		glyph.x = ReadAndGetInt("x", line);
		glyph.y = ReadAndGetInt("y", line);
		glyph.width = ReadAndGetInt("width", line);
		glyph.height = ReadAndGetInt("height", line);
		glyph.xoffset = ReadAndGetInt("xoffset", line);
		glyph.yoffset = ReadAndGetInt("yoffset", line);
		glyph.xadvance = ReadAndGetInt("xadvance", line);
		glyphMap[glyph.id] = glyph;
	}

	return true;
}

float Font::CalculateTextWidth(std::string text, float scale /*= 1.0f*/) {
	UNREFERENCED_PARAMETER(scale);
	uint cursor = 0;
	//int prev_char_code = -1;

	int currChar = 0;
	while (text[currChar] != NULL) {
		char c = text[currChar];
		glyphInfo const* glyph = GetGlyph(c);

		if (glyph == nullptr) {
			glyph = GetGlyph('~');
		}

		cursor += glyph->xadvance;
		//prev_char_code = *c;
		++currChar;

		//move cursor forward
		//int kerning = font->get_kerning(prev_char_code, *c);
		//cursor += kerning;
	}

	return (float)cursor;
}

glyphInfo* Font::GetGlyph(const char c) {
	return &glyphMap[(int)c];
}

int Font::ReadAndGetInt(std::string keyName, std::string textLine) {
	std::regex faceRegex(keyName + "=?(\\d+)");
	smatch match;
	regex_search(textLine, match, faceRegex);
	
	if (match.size() > 0) {
		string matchString = match.str(1);
		return stoi(matchString, nullptr, 10);
	}
	return NULL;
}

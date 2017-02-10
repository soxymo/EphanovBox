#include "Engine/Core/Rgba.hpp"

Rgba::Rgba() {
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}

Rgba::Rgba(unsigned char redByte, unsigned char greenByte, unsigned char blueByte, unsigned char alphaByte /*= 255*/) {
	r = redByte;
	g = greenByte;
	b = blueByte;
	a = alphaByte;
}

Rgba::Rgba(float normalizedRed, float normalizedGreen, float normalizedBlue, float normalizedAlpha /*= 1.0f*/) {
	r = (unsigned char)(normalizedRed * 255);
	g = (unsigned char)(normalizedGreen * 255);
	b = (unsigned char)(normalizedBlue * 255);
	a = (unsigned char)(normalizedAlpha * 255);
}

void Rgba::SetAsBytes(unsigned char redByte, unsigned char greenByte, unsigned char blueByte, unsigned char alphaByte) {
	r = redByte;
	g = greenByte;
	b = blueByte;
	a = alphaByte;
}

void Rgba::SetAsFloats(float normalizedRed, float normalizedGreen, float normalizedBlue, float normalizedAlpha /*= 1.0f*/) {
	r = (unsigned char)(normalizedRed * 255);
	g = (unsigned char)(normalizedGreen * 255);
	b = (unsigned char)(normalizedBlue * 255);
	a = (unsigned char)(normalizedAlpha * 255);
}

unsigned char* Rgba::GetAsCharArray() {
	return &r;
}

void Rgba::GetAsFloats(float& out_normalizedRed, float& out_normalizedGreen, float& out_normalizedBlue, float& out_normalizedAlpha) const {
	out_normalizedRed = (float)(r / 255.f);
	out_normalizedGreen = (float)(g / 255.f);
	out_normalizedBlue = (float)(b / 255.f);
	out_normalizedAlpha = (float)(a / 255.f);
}

void Rgba::ScaleRGB(float rgbScale) {
	ScaleAndClamp(r, rgbScale);
	ScaleAndClamp(g, rgbScale);
	ScaleAndClamp(b, rgbScale);
}

void Rgba::ScaleAlpha(float alphaScale) {
	ScaleAndClamp(a, alphaScale);
}

void Rgba::ScaleAndClamp(unsigned char& character, float scale) {
	if ((int)character * scale > 255)
		character = 255;
	if ((int)character *scale < 0)
		character = 0;
	character = (unsigned char)(character * scale);
}

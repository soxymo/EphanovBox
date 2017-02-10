#pragma once

class Rgba {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Rgba();
	explicit Rgba(unsigned char redByte, unsigned char greenByte,unsigned char blueByte, unsigned char alphaByte = 255);
	explicit Rgba(float normalizedRed, float normalizedGreen,float normalizedBlue, float normalizedAlpha = 1.0f);
	void SetAsBytes(unsigned char redByte, unsigned char greenByte, unsigned char blueByte, unsigned char alphaByte = 255);
	void SetAsFloats(float normalizedRed, float normalizedGreen, float normalizedBlue , float normalizedAlpha = 1.0f);
	unsigned char* GetAsCharArray();
	void GetAsFloats(float& out_normalizedRed, float& out_normalizedGreen, float& out_normalizedBlue, float& out_normalizedAlpha) const;
	void ScaleRGB(float rgbScale); // Scales (and clamps) RGB components, but not A
	void ScaleAlpha(float alphaScale); // Scales (and clamps) Alpha, RGB is untouched

private:
	void ScaleAndClamp(unsigned char& character, float scale);
};



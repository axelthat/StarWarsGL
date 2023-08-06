#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include "vendor/stbi_image.h"

class Texture {
private:
	static std::unordered_map<std::string, Texture> Textures;
	unsigned int m_Id;
	unsigned int width, height;
	unsigned int internal_format;
	unsigned int image_format;
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int filter_min;
	unsigned int filter_max;

public:
	inline unsigned int GetWidth() { return width; }
	inline unsigned int GetHeight() { return height; }

public:
	static void LoadTexture(const char* name, const char* file, bool isAlpha);
	static Texture& GetTexture(const char* name);
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind(unsigned int slot = 0) const;
};
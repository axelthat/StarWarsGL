#include "Texture.h"

std::unordered_map<std::string, Texture> Texture::Textures;

void Texture::LoadTexture(const char* name, const char* file, bool isAlpha) {
	Texture texture;

	if (isAlpha) {
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	int w, h, c;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &w, &h, &c, 0);
	if (data) {
		texture.Generate(w, h, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		Textures[name] = std::move(texture);
		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load texture!" << std::endl;
	}
}

Texture& Texture::GetTexture(const char* name)
{
	return Texture::Textures[name];
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data) {
	glGenTextures(1, &m_Id);
	wrap_s = GL_REPEAT;
	wrap_t = GL_REPEAT;
	filter_min = GL_NEAREST;
	filter_max = GL_NEAREST;

	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}
#pragma once
#include "renderer.h"

class texture
{

private:
	unsigned int rendererId;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;
public:
	texture(const std::string& path);
	~texture();

	void bind(unsigned int slot = 0) const; //every device's gpu you have texture slots for multiple textures
	void unbind() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; };
};

#include "texture.h"
#include "vendor/stb_image/stb_image.h"

texture::texture(const std::string& path)
: rendererId(0), filePath(path), localBuffer(nullptr), width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4); //4 = r g b a 

	glCall(glGenTextures(1, &rendererId));
	glCall(glBindTexture(GL_TEXTURE_2D, rendererId));

	//default parameters but have to mention otherwise we get a black screen
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//gltex....i i stands for integer type
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));//gllinear for linear sampling min and mag for scaling
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//wrap for streaching area s horozontal t vertical
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//clamp basically locks the area

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0 ,GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));

	if(localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}
texture::~texture()
{

	glCall(glDeleteTextures(1, &rendererId));

}

void texture::bind(unsigned int slot ) const
{
	//slot = 0 we will only be using texture slot 0 for now 
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, rendererId));

}
void texture::unbind() const 
{

	glCall(glBindTexture(GL_TEXTURE_2D, 0));

}


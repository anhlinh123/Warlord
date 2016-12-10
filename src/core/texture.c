#include "texture.h"

Texture* Texture_Create()
{
	Texture* texture = (Texture*) malloc(sizeof(Texture));
	texture->type = GL_TEXTURE_2D;
	texture->format = GL_RGB;
	texture->mipmapLevel = 0;
	texture->minFilter = GL_LINEAR;
	texture->magFilter = GL_LINEAR;
	texture->wrapS = GL_REPEAT;
	texture->wrapT = GL_REPEAT;
	texture->width = 1;
	texture->height = 1;
	texture->id = 0;
	return texture;
}

void Texture_Destroy(Texture* texture)
{
	free(texture);
}

void Texture_SetData(const char* data)
{
	
}
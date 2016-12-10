#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <core/config.h>
#include <opengl/glad.h>

typedef struct Texture
{
	GLenum type;
	GLenum format;
	GLuint mipmapLevel;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapS;
	GLenum wrapT;
	GLuint width;
	GLuint height;
	GLuint id;
} Texture;

Texture* Texture_Create();
void Texture_Destroy(Texture* texture);
void Texture_SetData(const char* data);
void Texture_Apply(Texture* texture);

#endif
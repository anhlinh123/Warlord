#include <opengl/glad.h>
#include "texture.h"

struct Texture
{
	GLenum type;
	GLenum format;
	GLuint width;
	GLuint height;
	GLuint mipmapLevelCount;
	GLenum minFilter;
	GLenum magFilter;
	GLuint id;
};

GLenum Texture_ToGLenum(int value)
{
	switch (value)
	{
	case TEXTURE_2D: return GL_TEXTURE_2D;
	case TEXTURE_3D: return GL_TEXTURE_3D;
	case TEXTURE_CUBE: return GL_TEXTURE_CUBE_MAP;
	case TEXTURE_ALPHA_8: return GL_ALPHA;
	case TEXTURE_LUMINANCE_ALPHA_88: return GL_LUMINANCE_ALPHA;
	case TEXTURE_RGB_888: return GL_RGB;
	case TEXTURE_RGBA_8888: return GL_RGBA;
	case FILTER_POINT: return GL_NEAREST;
	case FILTER_LINEAR: return GL_LINEAR;
	case FILTER_BILINEAR: return GL_LINEAR_MIPMAP_NEAREST;
	case FILTER_TRILLINEAR: return GL_LINEAR_MIPMAP_LINEAR;
	case WRAP_REPEAT: return GL_REPEAT;
	case WRAP_CLAMP: return GL_CLAMP;
	default: break;
	}
}

Texture* Texture_Create(const Texture_Desc* texture_desc)
{
	Texture* texture = (Texture*) malloc(sizeof(Texture));
	glGenTextures(1, &texture->id);
	Texture_Apply(texture, texture_desc);

	return texture;
}

void Texture_Destroy(Texture* texture)
{
	glDeleteTextures(1, &texture->id);
	free(texture);
}

void Texture_SetData(Texture* texture, uint32 mipmapLevel, const void* data)
{
	ASSERT(texture->mipmapLevelCount > mipmapLevel || mipmapLevel == 0);

	glBindTexture(texture->type, texture->id);
	switch (texture->type)
	{
	case GL_TEXTURE_2D:
	{
		glTexImage2D(GL_TEXTURE_2D, mipmapLevel, texture->format, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, data);
	}
	case GL_TEXTURE_CUBE_MAP:
	{
		//unsupported yet
	}
	default:
		break;
	}
	if (mipmapLevel == 0 && texture->mipmapLevelCount == 0 && (texture->minFilter > GL_LINEAR || texture->magFilter > GL_LINEAR))
	{
		glGenerateMipmap(texture->type);
	}
	glBindTexture(texture->type, 0);
}

void Texture_Apply(Texture* texture, const Texture_Desc* texture_desc)
{
	ASSERT(texture->id >= 0);

	GLenum type = Texture_ToGLenum(texture_desc->type);
	GLenum minFilter = Texture_ToGLenum(texture_desc->minFilter);
	GLenum magFilter = Texture_ToGLenum(texture_desc->magFilter);
	glBindTexture(type, texture->id);
	glTexParameteri(type, GL_TEXTURE_BASE_LEVEL, 0);
	if (texture_desc->mipmapLevelCount > 0)
		glTexParameteri(type, GL_TEXTURE_MAX_LEVEL, texture_desc->mipmapLevelCount - 1);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, Texture_ToGLenum(texture_desc->wrapS));
	glTexParameteri(type, GL_TEXTURE_WRAP_T, Texture_ToGLenum(texture_desc->wrapT));
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, Texture_ToGLenum(minFilter));
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, Texture_ToGLenum(magFilter));
	glBindTexture(type, 0);

	texture->type = type;
	texture->format = Texture_ToGLenum(texture_desc->format);
	texture->width = texture_desc->width;
	texture->height = texture_desc->height;
	texture->mipmapLevelCount = texture_desc->mipmapLevelCount;
	texture->minFilter = minFilter;
	texture->magFilter = magFilter;
}
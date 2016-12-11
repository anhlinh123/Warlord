#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <core/config.h>

typedef struct Texture_Desc
{
	Texture_Type type;
	Texture_Format format;
	uint32 width;
	uint32 height;
	uint32 mipmapLevelCount;
	Texture_Filter minFilter;
	Texture_Filter magFilter;
	Texture_Wrap wrapS;
	Texture_Wrap wrapT;
} Texture_Desc;

typedef struct Texture Texture;

Texture* Texture_Create(Texture_Desc* texture_desc);
void Texture_Destroy(Texture* texture);
void Texture_SetData(Texture* texture, uint32 mipmapLevel, const void* data);
void Texture_Apply(Texture* texture, Texture_Desc* texture_desc);

#endif
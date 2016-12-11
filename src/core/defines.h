#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef enum Texture_Type
{
	TEXTURE_2D = 0x0000,
	TEXTURE_3D = 0x0001,
	TEXTURE_CUBE = 0x0002
} Texture_Type;

typedef enum Texture_Format
{
	TEXTURE_ALPHA_8 = 0x0003,
	TEXTURE_LUMINANCE_ALPHA_88 = 0x0004,
	TEXTURE_RGB_888 = 0x0005,
	TEXTURE_RGBA_8888 = 0x0006
} Texture_Format;

typedef enum Texture_Filter
{
	FILTER_POINT = 0x0007,
	FILTER_LINEAR = 0x0008,
	FILTER_BILINEAR = 0x0009,
	FILTER_TRILLINEAR = 0x000a
} Texture_Filter;

typedef enum Texture_Wrap
{
	WRAP_REPEAT = 0x000b,
	WRAP_CLAMP = 0x000c
} Texture_Wrap;

#endif
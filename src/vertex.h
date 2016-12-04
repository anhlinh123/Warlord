#ifndef __VERTEX_H__
#define __VERTEX_H__

typedef union _f3
{
	struct
	{
		float x, y, z;
	};
	struct
	{
		float r, g, b;
	};
} _f3;

typedef union _f4
{
	struct
	{
		float x, y, z, w;
	};
	struct
	{
		float r, g, b, a;
	};
} _f4;

typedef struct Vertex
{
	_f3 position;
	_f4 color;
} Vertex;

#define VERTEX_ATTRIBUTE_COUNTS 2

typedef struct VertexAttribute
{
	const char* name;
	GLuint componentCounts;
	GLenum type;
	GLuint offset;
} VertexAttribute;

extern VertexAttribute VertexAttributes[];

#endif
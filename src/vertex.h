#ifndef __VERTEX_H__
#define __VERTEX_H__

union _f3
{
	struct
	{
		float x, y, z;
	};
	struct
	{
		float r, g, b;
	};
};

union _f4
{
	struct
	{
		float x, y, z, w;
	};
	struct
	{
		float r, g, b, a;
	};
};

struct Vertex
{
	_f3 position;
	_f4 color;
};

#define VERTEX_ATTRIBUTE_COUNTS 2

struct VertexAttribute
{
	const char* name;
	GLuint componentCounts;
	GLenum type;
	GLuint offset;
};

extern VertexAttribute VertexAttributes[];

#endif
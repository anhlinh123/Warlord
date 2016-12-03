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

#endif
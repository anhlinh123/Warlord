#ifndef __MATHS_H__
#define __MATHS_H__

typedef union float2
{
	struct
	{
		float x, y;
	};
	float data[2];
} float2;

typedef union float3
{
	struct
	{
		float x, y, z;
	};
	struct
	{
		float r, g, b;
	};
	float data[3];
} float3;

typedef union float4
{
	struct
	{
		float x, y, z, w;
	};
	struct
	{
		float r, g, b, a;
	};
	float data[4];
} float4;

typedef union matrix3x3
{
	struct
	{
		float a1, a2, a3;
		float b1, b2, b3;
		float c1, c2, c3;
	};
	float data2D[3][3];
	float data[9];
} matrix3x3;

typedef union matrix4x4
{
	struct
	{
		float a1, a2, a3, a4;
		float b1, b2, b3, b4;
		float c1, c2, c3, c4;
		float d1, d2, d3, d4;
	};
	float data2D[4][4];
	float data[16];
} matrix4x4;

#endif
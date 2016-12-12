#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "maths.h"

typedef struct Vertex
{
	float3 position;
	float3 normal;
	float3 tangent;
	float3 bitangent;
	float2 uv1;
	float2 uv2;
	float4 color;
} Vertex;

#define VERTEX_ATTRIBUTE_COUNTS 7

#endif
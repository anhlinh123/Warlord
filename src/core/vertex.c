#include <opengl/glad.h>
#include "vertex.h"

VertexAttribute VertexAttributes[] =
{
	{
		"aPosition", 3, GL_FLOAT, 0
	},
	{
		"aNormal", 3, GL_FLOAT, sizeof(float3)
	},
	{
		"aTangent", 3, GL_FLOAT, 2 * sizeof(float3)
	},
	{
		"aBitangent", 3, GL_FLOAT, 3 * sizeof(float3)
	},
	{
		"aUV1", 2, GL_FLOAT, 4 * sizeof(float3)
	},
	{
		"aUV2", 2, GL_FLOAT, 4 * sizeof(float3) + sizeof(float2)
	},
	{
		"aColor", 4, GL_FLOAT, 4 * sizeof(float3) + 2 * sizeof(float2)
	}
};
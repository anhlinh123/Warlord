#include <glad.h>
#include <vertex.h>

VertexAttribute VertexAttributes[] =
{
	{
		"aPosition", 3, GL_FLOAT, 0
	},
	{
		"aColor", 4, GL_FLOAT, 3 * sizeof(float)
	}
};
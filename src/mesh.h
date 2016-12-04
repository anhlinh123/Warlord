#ifndef __MESH_H__
#define __MESH_H__

#include <glad.h>
#include <vertex.h>

typedef struct Mesh
{
	GLuint boIds[2];
	GLuint indexCount;
} Mesh;

Mesh* Mesh_Create(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count);

#endif
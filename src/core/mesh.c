#include "mesh.h"
#include <stdlib.h>

struct Mesh
{
	GLuint boIds[2];
	GLuint indexCount;
	GLuint materialIndex;
};

Mesh* Mesh_Create(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count)
{
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));

	glGenBuffers(2, mesh->boIds);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->boIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->boIds[1]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * index_count, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mesh->indexCount = index_count;

	return mesh;
}

void Mesh_Destroy(Mesh* mesh)
{
	glDeleteBuffers(2, mesh->boIds);
	free(mesh);
}

void Mesh_BindBuffer(const Mesh* mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->boIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->boIds[1]);
}

void Mesh_UnbindBuffer(const Mesh* mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh_Draw(const Mesh* mesh)
{
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, 0);
}
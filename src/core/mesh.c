#include "mesh.h"
#include <opengl/glad.h>
#include <stdlib.h>

struct Mesh
{
	GLuint boIds[2];
	GLuint indexCount;
	GLuint materialIndex;
};

Mesh* Mesh_Create(const Mesh_Data* mesh_data)
{
	GLushort* indices = (GLushort*)malloc(sizeof(GLushort) * mesh_data->indexCount);
	for (int i = 0; i < mesh_data->indexCount; i++)
	{
		indices[i] = (GLushort)mesh_data->indices[i];
	}

	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));

	glGenBuffers(2, mesh->boIds);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->boIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->boIds[1]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh_data->vertexCount, mesh_data->vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * mesh_data->indexCount, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mesh->indexCount = mesh_data->indexCount;

	free(indices);

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
#include <mesh.h>
#include <stdlib.h>
//#include <assimp/cimport.h>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

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
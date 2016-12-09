#ifndef __MESH_H__
#define __MESH_H__

#include <glad.h>
#include <vertex.h>

typedef struct Mesh Mesh;

Mesh* Mesh_Create(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count);
void Mesh_Destroy(Mesh* mesh);

void Mesh_BindBuffer(const Mesh* Mesh);
void Mesh_UnbindBuffer(const Mesh* mesh);
void Mesh_Draw(const Mesh* mesh);

#endif
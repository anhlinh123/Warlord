#ifndef __MESH_H__
#define __MESH_H__

#include "config.h"
#include "vertex.h"

typedef struct Mesh_Data
{
	Vertex* vertices;
	uint32 vertexCount;
	uint32* indices;
	uint32 indexCount;
} Mesh_Data;

typedef struct Mesh Mesh;

Mesh* Mesh_Create(const Mesh_Data* mesh_data);
void Mesh_Destroy(Mesh* mesh);

void Mesh_BindBuffer(const Mesh* Mesh);
void Mesh_UnbindBuffer(const Mesh* mesh);
void Mesh_Draw(const Mesh* mesh);

#endif
#ifndef __FRAME_H__
#define __FRAME_H__

#include <config.h>
#include <maths.h>
#include <mesh.h>
#include <material.h>

typedef struct Chunk Chunk;

Chunk* Chunk_Create(Mesh* mesh, Material* material);
void Chunk_Destroy(Chunk* chunk);
void Chunk_Draw(Chunk* chunk);
Material* Chunk_Get_Material(Chunk* chunk);

#endif
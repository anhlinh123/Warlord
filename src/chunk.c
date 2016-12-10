#include <chunk.h>

struct Chunk
{
	Mesh* mesh;
	Material* material;
};

Chunk* Chunk_Create(Mesh* mesh, Material* material)
{
	ASSERT(mesh != NULL && material != NULL);
	Chunk* chunk = (Chunk*)malloc(sizeof(Chunk));
	chunk->mesh = mesh;
	chunk->material = material;
	return chunk;
}

void Chunk_Destroy(Chunk* chunk)
{
	free(chunk);
}

void Chunk_Draw(Chunk* chunk)
{
	Shader* shader = Material_Get_Shader(chunk->material);
	Shader_Use(shader);
	Mesh_BindBuffer(chunk->mesh);
	Shader_EnableVertexArray(shader);
	Material_Apply(chunk->material);
	Mesh_Draw(chunk->mesh);
	Mesh_UnbindBuffer(chunk->mesh);
}

Material* Chunk_Get_Material(Chunk* chunk)
{
	return chunk->material;
}
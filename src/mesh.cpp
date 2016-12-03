#include <mesh.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh()
{
}

Mesh::Mesh(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count)
{
	Load(vertices, vertex_count, indices, index_count);
}

Mesh::Mesh(const char* fileName)
{
	Load(fileName);
}

Mesh::~Mesh()
{
}

void Mesh::Load(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count)
{
	glGenBuffers(2, m_boIds);

	BindBuffer();
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * index_count, indices, GL_STATIC_DRAW);

	UnBindBuffer();

	m_indexCount = index_count;
}

void Mesh::Load(const char* fileName)
{
	const struct aiScene* scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	int x = 0;
}

void Mesh::BindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_boIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_boIds[1]);
}

void Mesh::UnBindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);
}
#ifndef __MESH_H__
#define __MESH_H__

#include <glad.h>
#include <vertex.h>

class Mesh
{
public:
	Mesh();
	Mesh(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count);
	Mesh(const char* fileName);
	~Mesh();

	void Load(const Vertex* vertices, int vertex_count, const GLushort* indices, int index_count);
	void Load(const char* fileName);
	void BindBuffer();
	void UnBindBuffer();
	void Draw();

private:
	GLuint m_boIds[2];
	GLuint m_indexCount;
};

#endif
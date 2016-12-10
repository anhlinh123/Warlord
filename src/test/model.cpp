#include "model.h"
#include "gason.h"

extern "C" {
#include <core/mesh.h>
#include <core/material.h>
}

char* ReadFile(const char* fileName)
{
	FILE* f = fopen(fileName, "rb");
	if (f == NULL)
		return NULL;

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* source = (char*)malloc(size + 1);
	fread(source, sizeof(char), size, f);
	source[size] = 0;
	fclose(f);

	return source;
}

Material* LoadMaterial(JsonValue value)
{
	Material* material = Material_Create();
	for (auto prop : value)
	{
		if (strcmp(prop->key, "shader") == 0)
		{
			char* shaderSrc = ReadFile(prop->value.toString());
			Shader* shader = Shader_Compile(shaderSrc);
			free(shaderSrc);
			Material_Set_Shader(material, shader);
		}
	}
	return material;
}

Mesh* LoadMesh(JsonValue value)
{
	FILE* f = fopen(value.toString(), "r");
	if (f == NULL)
		return NULL;

	int vertexCount = 0;
	fscanf(f, "NrVertices: %d\n", &vertexCount);
	Vertex* vertices = new Vertex[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		fscanf(f, "%*s pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%*f, %*f];\n", &vertices[i].position.x, &vertices[i].position.y, &vertices[i].position.z);
	}

	int indexCount = 0;
	fscanf(f, "NrIndices: %d\n", &indexCount);
	GLushort* indices = new GLushort[indexCount];
	for (int i = 0; i < indexCount / 3; i++)
	{
		fscanf(f, "%*d. %hu, %hu, %hu", &indices[i * 3], &indices[i * 3 + 1], &indices[i * 3 + 2]);
	}

	Mesh* mesh = Mesh_Create(vertices, vertexCount, indices, indexCount);
	delete[] vertices;
	delete[] indices;

	return mesh;
}

Model::Model(const char* fileName)
{
	char* source = ReadFile(fileName);
	char* endptr;
	JsonValue value;
	JsonAllocator allocator;
	int status = jsonParse(source, &endptr, &value, allocator);
	if (status != JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - source);
		exit(EXIT_FAILURE);
	}

	Mesh* mesh = NULL;
	Material* material = NULL;
	for (auto i : value)
	{
		if (strcmp(i->key, "Material") == 0)
		{
			material = LoadMaterial(i->value);
		}
		else if (strcmp(i->key, "Mesh") == 0)
		{
			mesh = LoadMesh(i->value);
		}
	}
	
	m_chunk = Chunk_Create(mesh, material);
}

Model::~Model()
{
	Chunk_Destroy(m_chunk);
}

void Model::Draw()
{
	Chunk_Draw(m_chunk);
}

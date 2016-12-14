#include "model.h"
#include "gason.h"
#include <string.h>
#include "TGA.h"

extern "C" {
#include <core/mesh.h>
#include <core/material.h>
#include <core/texture.h>
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
		if (strcmp(prop->key, "textures") == 0)
		{
			for (auto texprop : prop->value)
			{
				Texture_Desc desc =
				{
					TEXTURE_2D,
					TEXTURE_RGBA_8888,
					0,
					0,
					0,
					FILTER_BILINEAR,
					FILTER_LINEAR,
					WRAP_CLAMP,
					WRAP_CLAMP
				};
				int bpp;
				char* buffer = LoadTGA(texprop->value.toString(), (int*)&desc.width, (int*)&desc.height, &bpp);
				if (bpp == 24)
					desc.format == TEXTURE_RGB_888;
				else if (bpp == 32)
					desc.format == TEXTURE_RGBA_8888;

				Texture* texture = Texture_Create(&desc);
				Texture_SetData(texture, 0, buffer);
				delete[] buffer;
				Material_Set_Texture(material, texprop->key, &texture);
			}
		}
		else if (strcmp(prop->key, "shader") == 0)
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

	Mesh_Data mesh_data;
	fscanf(f, "NrVertices: %d\n", &mesh_data.vertexCount);
	mesh_data.vertices = new Vertex[mesh_data.vertexCount];
	for (int i = 0; i < mesh_data.vertexCount; i++)
	{
		fscanf(f, "%*s pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%*f, %*f];\n", &(mesh_data.vertices[i].position.x), &(mesh_data.vertices[i].position.y), &(mesh_data.vertices[i].position.z));
	}

	fscanf(f, "NrIndices: %d\n", &mesh_data.indexCount);
	mesh_data.indices = new uint32[mesh_data.indexCount];
	for (int i = 0; i < mesh_data.indexCount / 3; i++)
	{
		fscanf(f, "%*d. %u, %u, %u", &(mesh_data.indices[i * 3]), &(mesh_data.indices[i * 3 + 1]), &(mesh_data.indices[i * 3 + 2]));
	}

	Mesh* mesh = Mesh_Create(&mesh_data);
	delete[] mesh_data.vertices;
	delete[] mesh_data.indices;

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

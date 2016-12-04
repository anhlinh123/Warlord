#ifndef __SHADER_H__
#define __SHADER_H__

#include <config.h>
#include <glad.h>
#include <vertex.h>
#include <uthash.h>

typedef struct UniformLocation
{
	char name[INTRINSIC_STRING_LENGTH];
	GLuint location;
	UT_hash_handle hh;
} UniformLocation;

typedef struct Shader
{
	char fileName[INTRINSIC_STRING_LENGTH];
	GLuint program;
	GLuint attribLocations[VERTEX_ATTRIBUTE_COUNTS];
	UniformLocation* uniforms;
} Shader;

Shader* Shader_Create(const char* fileName);
void Shader_Destroy(Shader* shader);

#endif
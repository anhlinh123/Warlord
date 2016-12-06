#ifndef __SHADER_H__
#define __SHADER_H__

#include <config.h>
#include <glad.h>
#include <vertex.h>
#include <uthash.h>

typedef struct Uniform
{
	char name[INTRINSIC_STRING_LENGTH];
	GLuint location;
	UT_hash_handle hh;
} Uniform;

typedef struct Shader
{
	char fileName[INTRINSIC_STRING_LENGTH];
	GLuint program;
	GLuint attribLocations[VERTEX_ATTRIBUTE_COUNTS];
	Uniform* uniforms;
} Shader;

Shader* Shader_Create(const char* fileName);
void Shader_Destroy(Shader* shader);
GLint Shader_GetUniformLocation(const Shader* shader, const char* name);

#endif
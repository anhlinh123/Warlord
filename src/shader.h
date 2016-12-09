#ifndef __SHADER_H__
#define __SHADER_H__

#include <config.h>

typedef struct Shader Shader;

Shader* Shader_Create(const char* fileName);
void Shader_Destroy(Shader* shader);
void Shader_Use(Shader* shader);
void Shader_EnableVertexArray(Shader* shader);
GLint Shader_GetLocation(const Shader* shader, const char* name);

#endif
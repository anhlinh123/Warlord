#ifndef __SHADER_H__
#define __SHADER_H__

#include "config.h"
#include <opengl/glad.h>

typedef struct Shader Shader;

Shader* Shader_Compile(const char* sourceCode);
void Shader_Destroy(Shader* shader);
void Shader_Use(Shader* shader);
void Shader_EnableVertexArray(Shader* shader);
GLint Shader_GetLocation(const Shader* shader, const char* name);

#endif
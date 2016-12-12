#include "shader.h"
#include "vertex.h"
#include "khash.h"
#include <stdlib.h>
#include <opengl/glad.h>

#define LOG_SHADER_ERR(shader)											\
	GLint infoLen = 0;													\
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);				\
																		\
	if (infoLen > 1)													\
	{																	\
		char* infoLog = (char*)malloc(sizeof(char) * infoLen);			\
																		\
		glGetShaderInfoLog(shader, infoLen, NULL, infoLog);				\
		LOG_E("Error compiling shader:\n%s\n", infoLog);				\
																		\
		free(infoLog);													\
	}																	\

#define LOG_PROGRAM_ERR(program)										\
	GLint infoLen = 0;													\
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);				\
																		\
	if (infoLen > 1)													\
	{																	\
		char* infoLog = (char*)malloc(sizeof(char) * infoLen);			\
																		\
		glGetProgramInfoLog(program, infoLen, NULL, infoLog);			\
		LOG_E("Error linking program:\n%s\n", infoLog);					\
																		\
		free(infoLog);													\
	}																	\

KHASH_MAP_INIT_STR(location, GLuint)

typedef struct VertexAttribute
{
	const char* name;
	GLuint componentCounts;
	GLenum type;
	GLuint offset;
} VertexAttribute;

VertexAttribute VertexAttributes[] =
{
	{
		"aPosition", 3, GL_FLOAT, 0
	},
	{
		"aNormal", 3, GL_FLOAT, sizeof(float3)
	},
	{
		"aTangent", 3, GL_FLOAT, 2 * sizeof(float3)
	},
	{
		"aBitangent", 3, GL_FLOAT, 3 * sizeof(float3)
	},
	{
		"aUV1", 2, GL_FLOAT, 4 * sizeof(float3)
	},
	{
		"aUV2", 2, GL_FLOAT, 4 * sizeof(float3) + sizeof(float2)
	},
	{
		"aColor", 4, GL_FLOAT, 4 * sizeof(float3) + 2 * sizeof(float2)
	}
};

struct Shader
{
	char fileName[INTRINSIC_STRING_LENGTH];
	GLuint program;
	GLuint attribLocations[VERTEX_ATTRIBUTE_COUNTS];
	khash_t(location)* locations;
};

Shader* Shader_Compile(const char* sourceCode)
{
	ASSERT(sourceCode != NULL);

	const char* vertex = sourceCode;
	const char* fragment = strstr(sourceCode, "/*fragment shader*/");
	if (fragment == NULL)
	{
		LOG_E("Cannot find fragment shader.");
		return NULL;
	}

	GLint status = 0;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0)
	{
		LOG_E("Cannot create vertex shader");
		return NULL;
	}
	GLint size = fragment - vertex;
	glShaderSource(vertexShader, 1, &vertex, &size);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		LOG_SHADER_ERR(vertexShader);
		glDeleteShader(vertexShader);
		return NULL;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0)
	{
		LOG_E("Cannot create fragment shader");
		glDeleteShader(vertexShader);
		return NULL;
	}
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		LOG_SHADER_ERR(fragmentShader);
		glDeleteShader(fragmentShader);
		return NULL;
	}

	GLuint program = glCreateProgram();
	if (program == 0)
	{
		LOG_E("Error while creating a new shader program");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return NULL;
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		LOG_SHADER_ERR(program);
		glDeleteProgram(program);
		return NULL;
	}

	Shader* shader = (Shader*)malloc(sizeof(Shader));
	shader->program = program;

	for (int i = 0; i < VERTEX_ATTRIBUTE_COUNTS; i++)
	{
		shader->attribLocations[i] = glGetAttribLocation(program, VertexAttributes[i].name);
	}

	GLint count;
	GLchar name[16];

	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	LOG_I("Active Uniforms: %d\n", count);

	for (GLuint i = 0; i < count; i++)
	{
		glGetActiveUniform(program, i, 16, NULL, NULL, NULL, name);
		LOG_I("Uniform #%d Name: %s\n", i, name);

		GLint location = glGetUniformLocation(program, name);
		if (location >= 0)
		{
			int ret;
			khiter_t k = kh_put(location, shader->locations, name, &ret);
			if (ret != 0)
			{
				kh_value(shader->locations, k) = (GLuint)location;
			}
		}
	}

	return shader;
}

void Shader_Destroy(Shader* shader)
{
	kh_destroy(location, shader->locations);
	glDeleteProgram(shader->program);
	free(shader);
}

int32 Shader_GetLocation(const Shader* shader, const char* name)
{
	khiter_t k = kh_get(location, shader->locations, name);
	if (k != kh_end(shader->locations))
	{
		return kh_value(shader->locations, k);
	}
	return -1;
}

void Shader_Use(Shader* shader)
{
	glUseProgram(shader->program);
}

void Shader_EnableVertexArray(Shader* shader)
{
	for (int i = 0; i < VERTEX_ATTRIBUTE_COUNTS; i++)
	{
		glEnableVertexAttribArray(shader->attribLocations[i]);
		glVertexAttribPointer(shader->attribLocations[i], VertexAttributes[i].componentCounts, VertexAttributes[i].type, GL_FALSE, sizeof(Vertex), (const void*)(VertexAttributes[i].offset));
	}
}
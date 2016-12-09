#include <glad.h>
#include <vertex.h>
#include <khash.h>
#include <shader.h>
#include <stdlib.h>
#include <stdio.h>

KHASH_MAP_INIT_STR(location, GLuint)

struct Shader
{
	char fileName[INTRINSIC_STRING_LENGTH];
	GLuint program;
	GLuint attribLocations[VERTEX_ATTRIBUTE_COUNTS];
	khash_t(location)* locations;
};

GLuint Shader_Load(GLenum type, const char* fileName)
{
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);
	if (shader == 0)
		return 0;

	// Load the shader source
	FILE * pf;
	if (fopen_s(&pf, fileName, "rb") != 0)
		return NULL;
	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char* shaderSrc = (char*)malloc(size + 1);
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = 0;
	fclose(pf);

	glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
	free(shaderSrc);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			LOG_E("Error compiling shader <%s>:\n%s\n", fileName, infoLog);

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

Shader* Shader_Create(const char* fileName)
{
	Shader* shader = (Shader*)malloc(sizeof(Shader));

	char realName[64];
	strcpy(realName, fileName);
	strcat(realName, ".vs");
	GLuint vertex = Shader_Load(GL_VERTEX_SHADER, realName);
	if (vertex == 0)
	{
		LOG_E("Error while creating %s vertex shader", fileName);
		return;
	}

	strcpy(realName, fileName);
	strcat(realName, ".fs");
	GLuint fragment = Shader_Load(GL_FRAGMENT_SHADER, realName);
	if (vertex == 0)
	{
		LOG_E("Error while creating %s fragment shader", fileName);
		glDeleteShader(vertex);
		return;
	}

	GLuint program = glCreateProgram();
	if (program == 0)
	{
		LOG_E("Error while creating a new shader program");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		GLint infoLen = 0;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			LOG_E("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(program);
		return;
	}

	shader->program = program;

	// Cache all attributes and uniforms info
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
		LOG_I("Uniform #%d Type: %u Name: %s\n", i, type, name);

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

GLint Shader_GetLocation(const Shader* shader, const char* name)
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
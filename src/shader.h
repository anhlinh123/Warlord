#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad.h>
#include <unordered_map>
#include <config.h>
#include <vertex.h>

class Shader
{
public:
	Shader();
	Shader(const char* fileName);
	~Shader();

	void Load(const char* fileName);
	void UseProgram();
	void EnableVertexAttribArray();

private:
	char* m_fileName;
	GLuint m_program;
	GLuint m_attribLocations[VERTEX_ATTRIBUTE_COUNTS];
	std::unordered_map<std::string, GLuint> m_uniformMap;

	GLuint LoadShader(GLenum type, const char* fileName);
};

#endif
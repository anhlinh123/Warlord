#include <shader.h>

Shader::Shader()
{

}

Shader::Shader(const char* fileName)
{
	Load(fileName);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::Load(const char* fileName)
{
	std::string vertexFile = fileName;
	vertexFile += ".vs";
	GLuint vertex = LoadShader(GL_VERTEX_SHADER, vertexFile.c_str());
	if (vertex == 0)
	{
		LOG_E("Error while creating %s vertex shader", fileName);
		return;
	}

	std::string fragmentFile = fileName;
	fragmentFile += ".fs";
	GLuint fragment = LoadShader(GL_FRAGMENT_SHADER, fragmentFile.c_str());
	if (vertex == 0)
	{
		LOG_E("Error while creating %s fragment shader", fileName);
		glDeleteShader(vertex);
		return;
	}

	m_program = glCreateProgram();
	if (m_program == 0)
	{
		LOG_E("Error while creating a new shader program");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return;
	}

	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glLinkProgram(m_program);

	GLint linkStatus;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		GLint infoLen = 0;

		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[sizeof(char) * infoLen];

			glGetProgramInfoLog(m_program, infoLen, NULL, infoLog);
			LOG_E("Error linking program:\n%s\n", infoLog);

			delete infoLog;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(m_program);
		return;
	}

	// Cache all attributes and uniforms info
	for (int i = 0; i < VERTEX_ATTRIBUTE_COUNTS; i++)
	{
		m_attribLocations[i] = glGetAttribLocation(m_program, VertexAttributes[i].name);
	}

	GLint count;
	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL

	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);
	LOG_I("Active Uniforms: %d\n", count);

	for (GLuint i = 0; i < count; i++)
	{
		glGetActiveUniform(m_program, i, bufSize, NULL, NULL, NULL, name);
		LOG_I("Uniform #%d Type: %u Name: %s\n", i, type, name);

		GLint location = glGetUniformLocation(m_program, name);
		if (location >= 0)
		{
			m_uniformMap[name] = (GLuint)location;
		}
	}
}

GLuint Shader::LoadShader(GLenum type, const char* fileName)
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

	char * shaderSrc = new char[size + 1];
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = 0;
	fclose(pf);

	glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
	delete[] shaderSrc;

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
			char* infoLog = new char[infoLen];


			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			LOG_E("Error compiling shader <%s>:\n%s\n", fileName, infoLog);

			delete[] infoLog;
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

void Shader::UseProgram()
{
	glUseProgram(m_program);
}

void Shader::EnableVertexAttribArray()
{
	for (int i = 0; i < VERTEX_ATTRIBUTE_COUNTS; i++)
	{
		glEnableVertexAttribArray(m_attribLocations[i]);
		glVertexAttribPointer(m_attribLocations[i], VertexAttributes[i].componentCounts, VertexAttributes[i].type, GL_FALSE, sizeof(Vertex), (const void*)(VertexAttributes[i].offset));
	}
}
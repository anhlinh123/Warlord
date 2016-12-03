#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vertex.h"
#include <shader.h>

GLuint vboId;
Shader shader;

void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//triangle data (heap)
	Vertex verticesData[3];

	verticesData[0].position.x = 0.0f;  verticesData[0].position.y = 0.5f;  verticesData[0].position.z = 0.0f;
	verticesData[1].position.x = -0.5f;  verticesData[1].position.y = -0.5f;  verticesData[1].position.z = 0.0f;
	verticesData[2].position.x = 0.5f;  verticesData[2].position.y = -0.5f;  verticesData[2].position.z = 0.0f;

	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f; verticesData[0].color.a = 1.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f; verticesData[1].color.a = 1.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f; verticesData[2].color.a = 1.0f;

	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//create shader
	shader.Load("triangle");
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	shader.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	shader.EnableVertexAttribArray();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	Init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vertex.h"
#include <shader.h>
#include <mesh.h>

Mesh mesh;
Shader shader;

void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	mesh.Load("M4A1.dae");
	shader.Load("triangle");
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	shader.UseProgram();
	mesh.BindBuffer();
	shader.EnableVertexAttribArray();
	mesh.Draw();
	mesh.UnBindBuffer();
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
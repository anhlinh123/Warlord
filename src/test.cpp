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

	Vertex verticesData[3];

	verticesData[0].position.x = 0.0f;  verticesData[0].position.y = 0.5f;  verticesData[0].position.z = 0.0f;
	verticesData[1].position.x = -0.5f;  verticesData[1].position.y = -0.5f;  verticesData[1].position.z = 0.0f;
	verticesData[2].position.x = 0.5f;  verticesData[2].position.y = -0.5f;  verticesData[2].position.z = 0.0f;

	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f; verticesData[0].color.a = 1.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f; verticesData[1].color.a = 1.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f; verticesData[2].color.a = 1.0f;

	GLushort indices[] = { 0, 1, 2 };

	mesh.Load(verticesData, 3, indices, 3);
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
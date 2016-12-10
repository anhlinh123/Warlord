#include <config.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <model.h>

Model* model;

void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	model = new Model("test.model");
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	model->Draw();
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
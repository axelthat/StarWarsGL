#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "Input.h"
#include "Game.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) {
			Input::keys[key] = true;
		}

		if (action == GLFW_RELEASE) {
			Input::keys[key] = false;
			Input::keyUp[key] = false;
		}
	}
}

int main(void)
{
	unsigned int width = 1920;
	unsigned int height = 1080;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (version == 0) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Loaded OpenGL " << glGetString(GL_VERSION) << std::endl;

	Game game = Game(width, height);
	game.onInit();

	float currentTime = 0.0f;
	float lastTime = 0.0f;
	float delta = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.onUpdate(delta);
		game.onRender();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glfwTerminate();
	return 0;
}
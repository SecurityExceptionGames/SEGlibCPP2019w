#include <iostream>

#define GLFW_DLL
#include <glfw/glfw3.h>

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Library link test window", NULL, NULL);
	glfwShowWindow(window);

	while (!glfwWindowShouldClose(window))
		glfwPollEvents();

	std::cout << "Hello world!" << std::endl;
	return 0;
}
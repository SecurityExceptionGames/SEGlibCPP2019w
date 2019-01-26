#include <iostream>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>

#define GLFW_DLL
#include <glad/glad.h>
#include <glfw/glfw3.h>

using namespace org::segames::library;
using namespace org::segames::library::math;

int main()
{
	try
	{
		if (!glfwInit())
			return -1;

		vec3f a = { 2, 3, 0 };
		vec3f b = { -1, 0, 1 };

		std::cout << cross(a, b) << std::endl;

		GLFWwindow* window = glfwCreateWindow(800, 600, "Library link test window", NULL, NULL);
		glfwShowWindow(window);
		glfwMakeContextCurrent(window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, 800, 600);
			
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			glOrtho(0, 800, 600, 0, -1, 1);

			glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex2f(100, 100);
			glColor3f(0, 1, 0);
			glVertex2f(500, 100);
			glColor3f(0, 0, 1);
			glVertex2f(500, 500);
			glEnd();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		std::cout << "Hello world!" << std::endl;
	}
	catch (Exception& e)
	{
		e.print();
	}

	return 0;
}
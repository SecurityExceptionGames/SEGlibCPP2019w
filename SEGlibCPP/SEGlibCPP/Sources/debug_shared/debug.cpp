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

		mat3f myMat = mat3f::rotation(radians(45000.0), vec3f(1, 0, 0));

		std::cout << std::endl << myMat << std::endl;
		
		vec3f a = { 2, 3, 0 };
		vec3f b = vec3f::rand();

		std::cout << cross(a, b) << std::endl;

		mat4f projMat;
		projMat = mat4f::ortho(0, 800, 600, 0, 0.1f, 10);

		std::cout << projMat << std::endl;

		GLFWwindow* window = glfwCreateWindow(1280, 800, "Library link test window", NULL, NULL);
		glfwShowWindow(window);
		glfwMakeContextCurrent(window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		float count = 1;
		while (!glfwWindowShouldClose(window))
		{

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, 1280, 800);
			
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			glLoadMatrixf(projMat.getPointer());

			glMatrixMode(GL_MODELVIEW_MATRIX);
			glLoadIdentity();
			glTranslatef(0, 0, 1);
			//glRotatef(count, 0, 0, 1);

			glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(-5.0f, -5.0f, 0);
			glColor3f(0, 1, 0);
			glVertex3f(10, -10, 0);
			glColor3f(0, 0, 1);
			glVertex3f(10, 10, 0);
			glEnd();

			glfwPollEvents();
			glfwSwapBuffers(window);

			if (count > 360)
				count = 0;
			else
				count += 0.5f;
		}

		std::cout << "Hello world!" << std::endl;
	}
	catch (Exception& e)
	{
		e.print();
	}

	return 0;
}
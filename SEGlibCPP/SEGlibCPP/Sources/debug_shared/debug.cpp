#include <org/segames/library/core.h>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>
#include <org/segames/library/util/timer.h>
#include <org/segames/library/util/linked_list.h>
#include <org/segames/library/util/array_queue.h>
#include <org/segames/library/util/array_stack.h>
#include <org/segames/library/util/array.h>
#include <org/segames/library/glfw/glfw_window.h>

#include <unordered_map>

#include <iostream>

#define GLFW_DLL
#include <glad/glad.h>
#include <glfw/glfw3.h>

using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;
using namespace org::segames::library::glfw;

int main()
{
	try
	{
		if (!glfwInit())
			return -1;

		GLFWWindow win;
		win.setSize(1280, 800);
		win.setTitle("Library link test window");
		win.setVisible(true);
		win.makeContextCurrent();
		
		bool entered = false, borderless = false;
		float count = 1;
		while (!win.isCloseRequested())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, 1280, 800);
			
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			glOrtho(0, win.getWidth(), win.getHeight(), 0, -1, 1);

			glMatrixMode(GL_MODELVIEW_MATRIX);
			glLoadIdentity();
			glTranslatef(0, 0, 1);
			glRotatef(count, 0, 0, 1);

			glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(-5.0f, -5.0f, 0);
			glColor3f(0, 1, 0);
			glVertex3f(10, -10, 0);
			glColor3f(0, 0, 1);
			glVertex3f(10, 10, 0);
			glEnd();

			win.pollEvents();
			win.swapBuffers();

			if (count > 360)
				count = 0;
			else
				count += 0.05f;
		}

		std::cout << "Hello world!" << std::endl;
	}
	catch (Exception& e)
	{
		e.print();
	}

	return 0;
}
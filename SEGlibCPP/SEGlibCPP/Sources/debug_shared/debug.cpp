#include <org/segames/library/core.h>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>
#include <org/segames/library/util/timer.h>
#include <org/segames/library/util/linked_list.h>
#include <org/segames/library/util/array_queue.h>
#include <org/segames/library/util/array_stack.h>
#include <org/segames/library/util/array.h>

#include <iostream>

#define GLFW_DLL
#include <glad/glad.h>
#include <glfw/glfw3.h>

using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;

class Stuff :
	public Object
{
public:
	char a[4096];
};

template<typename Itr>
void voidvoid(const Iterable<int, Itr>& itr)
{
	auto i = itr.begin();
	std::cout << (size_t)&i << std::endl;
}

int main()
{
	try
	{
		if (!glfwInit())
			return -1;

		{
			LinkedList<int> list;
			
			for (int i = 0; i < 10; i++)
				list.add(10 * (i + 1));
		
			for (auto i : list)
				std::cout << i << std::endl;

			voidvoid(list);
		}

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
			glOrtho(0, 1280, 800, 0, -1, 1);

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
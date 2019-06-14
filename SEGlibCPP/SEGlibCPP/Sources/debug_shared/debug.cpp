#include <org/segames/library/core.h>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>
#include <org/segames/library/util/timer.h>
#include <org/segames/library/gl/gl_pointer_inf.h>
#include <org/segames/library/glfw/glfw_window.h>
#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/gl/gl_backed_buffer.h>
#include <org/segames/library/gl/gl_pointer_binding.h>
#include <org/segames/library/gl/gl_core.h>

#include <unordered_map>
#include <thread>
#include <iostream>

using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;
using namespace org::segames::library::glfw;
using namespace org::segames::library::gl;

int main()
{
	try
	{
		GLFWWindow win;
		win.setSize(1280, 800);
		win.setTitle("Library link test window");
		win.setVisible(true);
		win.makeContextCurrent();

		GLShader shader;
		shader.loadVertexData("test/test.vert");
		shader.loadFragmentData("test/test.frag");
		shader.upload();

		GLFloatBuffer vert(GLDataType::VERTEX, GLPointerInf::TWO_FLOAT_POINTER);
		vert.push(0).push(0);
		vert.push(1).push(0);
		vert.push(1).push(1);
		vert.upload();

		GLFloatBuffer col(GLDataType::COLOR, GLPointerInf::THREE_FLOAT_POINTER);
		col.push(1).push(0).push(0);
		col.push(0).push(1).push(0);
		col.push(0).push(0).push(1);
		col.upload();

		GLFloatBuffer dou;
		dou.setPointerBinding(GLDataType::VERTEX, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 5, 0));
		dou.setPointerBinding(GLDataType::COLOR, GLPointerInf(GL_FLOAT, 3, sizeof(GLfloat) * 5, sizeof(GLfloat) * 2));
		dou.push(0).push(0);
		dou.push(1).push(0).push(0);
		dou.push(1).push(0);
		dou.push(0).push(1).push(0);
		dou.push(1).push(1);
		dou.push(0).push(0).push(1);
		dou.upload();
		
		std::cout << GLCore::glVersion() << std::endl;

		bool lock = false;
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
			/*glTranslatef(0, 0, 1);
			glRotatef(count, 0, 0, 1);*/

			dou.bind().setPointerInf();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);

			dou.release();

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
#include <org/segames/library/core.h>
#include <org/segames/library/system.h>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>
#include <org/segames/library/util/timer.h>
#include <org/segames/library/gl/gl_pointer_inf.h>
#include <org/segames/library/glfw/glfw_window.h>
#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/gl/gl_backed_buffer.h>
#include <org/segames/library/gl/gl_pointer_binding.h>
#include <org/segames/library/gl/gl_core.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/gl/texture/gl_physical_texture_wrapper.h>
#include <org/segames/library/gl/fbo/gl_framebuffer_wrapper.h>

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

		GLException::enableDebugCallback();

		GLShader shader;
		shader.loadVertexData("test/test.vert");
		shader.loadFragmentData("test/test.frag");
		shader.upload();

		GLPhysicalTextureWrapper tex("C:/Users/Philip R/Desktop/plan_flat.dds");
		tex.importTexture();
		tex.upload();

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

		GLFloatBuffer dou2;
		dou2.setPointerBinding(GLDataType::VERTEX, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.setPointerBinding(GLDataType::TEX_COORD, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.push(0).push(0);
		dou2.push(1).push(0);
		dou2.push(1).push(1);
		dou2.push(0).push(1);
		dou2.upload();

		GLFramebufferWrapper fbo(
			true,
			false,
			Dimension2i(1280, 800)
		);
		fbo.build();

		bool lock = false;
		float count = 1;
		while (!win.isCloseRequested())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, win.getWidth(), win.getHeight());
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 1, 1, 0, -1, 1);

			/*glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();*/

			fbo.bind();
			tex.bind();
			dou2.bind().setPointerInf();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			dou2.release();
			tex.release();
			fbo.release();

			fbo.getColorComp()->bind();
			dou2.bind().setPointerInf();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			dou2.release();
			fbo.getColorComp()->release();

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
#ifndef SEG_API_DLL

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
#include <org/segames/library/gl/text/gl_font.h>

#include <unordered_map>
#include <thread>
#include <iostream>

using namespace org::segames::library;

int main()
{
	try
	{
		GLFWWindow win;
		win.setSize(1280, 800);
		win.setPositionCenter();
		win.setTitle("Library link test window");
		win.setVisible(true);
		win.makeContextCurrent();
		win.setSwapInterval(1);

		GLException::enableDebugCallback();

		GLShader shader;
		shader.loadVertexData("test/test.vert");
		shader.loadFragmentData("test/test.frag");
		shader.upload();

		GLPhysicalTextureWrapper tex("C:/Users/Philip R/Desktop/plan_flat.dds");
		tex.importTexture();
		tex.upload();

		GLFloatBuffer dou2;
		dou2.setPointerBinding(GLDataType::VERTEX, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.setPointerBinding(GLDataType::TEX_COORD, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.push(0).push(0);
		dou2.push(1).push(0);
		dou2.push(1).push(1);
		dou2.push(0).push(1);
		dou2.upload();

		//vvv TODO REMOVE THIS vvv
		ArrayList<unsigned int> chars;
		for (unsigned int i = 32; i < 127; i++)
			chars.add(i);
		//^^^ TODO REMOVE THIS ^^^
		
		GLFont font(20, 2, "test/times.ttf", nullptr, chars.pointer(), chars.size());
		font.upload();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		bool lock = false;
		float count = 1;
		Timer rec;
		while (!win.isCloseRequested())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, win.getWidth(), win.getHeight());
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 1, 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			tex.bind();
			dou2.bind().setPointerInf();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			dou2.release();
			tex.release();

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, win.getWidth(), win.getHeight(), 0, -1, 1);

			std::string s = "[L][o]rem ipsum dolor\nsit amet, consectetur adipiscing elit. Mauris eu risus rutrum,\ncommodo tellus vitae,";
			font.render(win.getWidth() / 2, win.getHeight() / 2 - font.getHeight() * 1.5f, GLFontAlignment::CENTER, s, Color::GREEN);

			win.pollEvents();
			win.swapBuffers();

			if (count > 360)
				count = 0;
			else
				count += 0.05f;

			win.setTitle("Time: " + std::to_string(rec.deltaTime()) + "s");
		}

		std::cout << "Hello world!" << std::endl;
	}
	catch (Exception& e)
	{
		e.print();
	}

	return 0;
}

#endif
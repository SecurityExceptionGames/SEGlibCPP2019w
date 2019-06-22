#pragma once
#include <org/segames/library/glfw/glfw_listener.h>
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A window size listener for GLFW.

				* @author	Philip Rosberg
				* @since	2019-05-08
				* @edited	2019-05-08
			*/
			class SEG_API GLFWWindowSizeListener :
				public Object,
				public GLFWListener<GLFWWindowSizeListener>
			{
			private:

				/*
					Callback for GLFW.
				*/
				static void callback(GLFWwindow* window, int w, int h);

			public:

				/*
					Unlinks the callback for the given window.
					* @param[in] window The GLFW window id
				*/
				static void detach(GLFWwindow* window);

			protected:

				/*
					Window width.
				*/
				int m_w;

				/*
					Window height.
				*/
				int m_h;

				/*
					Links this listener to GLFW.
					* @param[in] window The GLFW window id
				*/
				virtual void linkGLFW(GLFWwindow* window) override;

			public:

				/*
					Returns the window width.
				*/
				virtual int getWidth() const;

				/*
					Returns the window height.
				*/
				virtual int getHeight() const;

				/*
					The method that is called when the listener is activated.
					* @param[in] w The window width
					* @param[in] h The window height
				*/
				virtual void invoke(int w, int h);

			};

		}

	}

}